#include "pch.h"
#include "Window.h"
#include "JProject.h"


#include "TestProject.h"

// ������Ʈ �Ӽ�->��Ŀ->�ý���->�ܼ�
//int main

// ������Ʈ �Ӽ�->��Ŀ->�ý���->â
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		WindowDesc desc;
		{
			desc.appName    = L"JProject";
			desc.vsync      = false;
			desc.width      = 1920;
			desc.height     = 1080;
			desc.clearColor = Color(Colors::Black);
			desc.app = makeSptr<JProject>();
			//desc.app = makeSptr<TestProject>();
		}

		WINDOW->Run(desc);
	}
	catch (Exception& e)
	{
		JLOG_ERROR(e.ToString().c_str());
	}
	
	return 0;
}