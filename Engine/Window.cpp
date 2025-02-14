#include "pch.h"
#include "Window.h"
#include "IExecute.h"
#include "FreeCamera.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Window::Update()
{
	TIME ->Update();
	INPUT->Update();

	DX ->RenderBegin();
	{
		// 게임 루프
		_desc.app->Loop();

		

		// ImGui 루프
		GUI->RenderBegin();
		GUI->Update();
		GUI->RenderEnd();
	}
	DX ->RenderEnd();
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
		//LOG->Init();
		JLOG->Init();
		DX->Init(_desc);
		ASSET->Init();
		GUI->Init();
		INPUT->Init();
		TIME->Init();
		FACTORY->Init();
		OBJECT->Init();
		SCENE->Init();
		//RENDERER->Init();
	}


	// MultiThreads Practice
	//std::thread GUI_Thread(&ImGuiManager::GUI_Thread, GUI->GetInstance());


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
		//GUI->Destroy();
		//GUI_Thread.join();

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

		JLOG_INFO("Size Changed");

		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return ::DefWindowProc(handle, message, wParam, lParam);
}
