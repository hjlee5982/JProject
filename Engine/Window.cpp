#include "pch.h"
#include "Window.h"
#include "IExecute.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Window::Update()
{
	TIME->Update();
	INPUT->Update();

	DX->RenderBegin();
	
	GUI->Update();

	_desc.app->Update();
	_desc.app->LateUpdate();
	_desc.app->Render();

	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	DX->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	D3D11_TEXTURE2D_DESC backBufferDesc;
	backBuffer->GetDesc(&backBufferDesc);

	D3D11_TEXTURE2D_DESC desc = backBufferDesc;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;

	ComPtr<ID3D11Texture2D> texture = nullptr;
	hr = DEVICE->CreateTexture2D(&desc, nullptr, texture.GetAddressOf());
	CHECK(hr);

	CONTEXT->CopyResource(texture.Get(), backBuffer.Get());




	D3D11_MAPPED_SUBRESOURCE mappedResource;
	hr = CONTEXT->Map(texture.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);
	CHECK(hr);

	BYTE* pData = reinterpret_cast<BYTE*>(mappedResource.pData);
	vector<BYTE> imageData(backBufferDesc.Width * backBufferDesc.Height * 4);
	memcpy(imageData.data(), pData, imageData.size());

	CONTEXT->Unmap(texture.Get(), 0);


	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = backBufferDesc.Width;
	textureDesc.Height = backBufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = backBufferDesc.Format;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = imageData.data();
	initData.SysMemPitch = backBufferDesc.Width * 4;

	ComPtr<ID3D11Texture2D> pTexture = nullptr;
	hr = DEVICE->CreateTexture2D(&textureDesc, &initData, pTexture.GetAddressOf());
	CHECK(hr);

	ComPtr<ID3D11ShaderResourceView> srv = nullptr;
	hr = DEVICE->CreateShaderResourceView(pTexture.Get(), nullptr, srv.GetAddressOf());
	CHECK(hr);



	ImGui::Begin("Test");
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::Image((void*)srv.Get(), ImVec2(size.x-15, size.y-36));

	ImGui::End();

	ImGui::Begin("Test2");
	ImGui::End();

	ImGui::Begin("Test3");
	ImGui::End();

	DX->ClearRenderTarget();

	GUI->Render();
	

	DX->RenderEnd();

}

WPARAM Window::Run(WindowDesc& desc)
{
	_desc = desc;

	MyRegisterClass();

	if (!InitInstance(SW_SHOWNORMAL))
	{
		return FALSE;
	}

	// SINGLETON INIT
	{
		LOG->Init();
		DX->Init(_desc);
		RESOURCE->Init();
		GUI->Init();
		INPUT->Init(_desc.hWnd, _desc.hInstance);
		TIME->Init();
		//RENDERER->Init();
	}

	_desc.app->Init();

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		Update();
	}

	// RELEASE
	{
		GUI->Shutdown();
		spdlog::shutdown();
	}

	return msg.wParam;
}

ATOM Window::MyRegisterClass()
{
	WNDCLASSEXW wcex;
	{
		wcex.cbSize        = sizeof(WNDCLASSEX);
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = WndProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = _desc.hInstance = GetModuleHandle(NULL);
		wcex.hIcon         = ::LoadIcon(NULL, IDI_WINLOGO);
		wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName  = NULL;
		wcex.lpszClassName = _desc.appName.c_str();
		wcex.hIconSm       = wcex.hIcon;
	}

	return RegisterClassExW(&wcex);
}

BOOL Window::InitInstance(i32 cmdShow)
{
	RECT windowRect = { 0, 0, _desc.width, _desc.height };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	_desc.hWnd = CreateWindowW
	(
		_desc.appName.c_str(),
		_desc.appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		_desc.hInstance,
		nullptr
	);

	if (!_desc.hWnd)
	{
		return FALSE;
	}
	
	::ShowWindow(_desc.hWnd, cmdShow);
	::UpdateWindow(_desc.hWnd);
	
	return TRUE;
}

LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam))
	{
		return true;
	}

	switch (message)
	{
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(handle);
			break;
		}

		break;
	case WM_SIZE:
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return ::DefWindowProc(handle, message, wParam, lParam);
}
