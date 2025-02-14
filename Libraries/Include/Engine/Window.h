#pragma once

struct WindowDesc
{
	sptr<class IExecute> app = nullptr;

	wstring   appName;
	HINSTANCE hInstance;
	HWND      hWnd;
	f32       width;
	f32       height;
	bool      vsync;
	bool      windowed;
	Color     clearColor;
};

class Window
{
	SINGLETON(Window);
public:
	WPARAM Run(WindowDesc& desc);
private:
	void Update();
private:
	ATOM MyRegisterClass();
	BOOL InitInstance(i32 cmdShow);
public:
	WindowDesc& GetGameDesc()
	{ 
		return _desc; 
	}
private:
	WindowDesc _desc;
public:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
private:
	std::mutex _mutex;
};

