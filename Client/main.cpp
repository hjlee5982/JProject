#include "pch.h"
#include "Window.h"
#include "JProject.h"

int main()
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
			desc.app        = makeSptr<JProject>();
		}

		WINDOW->Run(desc);
	}
	catch (Exception& e)
	{
		LOG_ERROR(e.ToString());
	}

	return 0;
}