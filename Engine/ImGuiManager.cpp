#include "pch.h"
#include "ImGuiManager.h"
#include "ImWindow.h"
#include "ImScene.h"
#include "ImInspector.h"
#include "ImProject.h"
#include "ImConsole.h"
#include "Imhierarchy.h"
#include "ImDockSpace.h"

void ImGuiManager::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.Fonts->AddFontFromFileTTF("../Assets/Font/Inter-SemiBold.ttf", 15.f);
    //_koreanFont = io.Fonts->AddFontFromFileTTF("../Assets/Font/NanumGothic-Bold.ttf", 15.f, NULL, io.Fonts->GetGlyphRangesKorean());

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    io.ConfigDockingAlwaysTabBar = true;

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    
    style.TabRounding    = 5.f;
    style.FrameRounding  = 8.f;
    style.GrabRounding   = 8.f;
    style.WindowRounding = 8.f;
    style.PopupRounding  = 8.f;

    {
        {
            auto& colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

            // Menu
            colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.f, 0.f, 0.f, 1.f };

            // Headers
            colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Buttons
            colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Frame BG
            colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Tabs
            colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
            colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
            colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

            // Title
            colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        }
        //{
        //    auto& colors = ImGui::GetStyle().Colors;

        //    // 창 배경 색
        //    colors[ImGuiCol_WindowBg] = ImVec4{ 0.22f, 0.22f, 0.22f, 1.0f };

        //    // Headers, 계층구조 선택되었을 때
        //    colors[ImGuiCol_Header] = ImVec4{ 1.f, 1.f, 1.f, 1.0f };
        //    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.267f, 0.267f, 0.267f, 1.0f };
        //    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.172f, 0.365f, 0.530f, 1.0f };

        //    // Buttons, 버튼 색
        //    colors[ImGuiCol_Button] = ImVec4{ 0.345f, 0.345f, 0.345f, 1.0f };
        //    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.404f, 0.404f, 0.404f, 1.0f };
        //    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.274f, 0.376f, 0.486f, 1.0f };

        //    // Frame BG, 슬라이더 등등 색
        //    colors[ImGuiCol_FrameBg] = ImVec4{ 0.165f, 0.165f, 0.165f, 1.0f };
        //    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.267f, 0.267f, 0.267f, 1.0f };
        //    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.302f, 0.302f, 0.302f, 1.0f };

        //    // Tabs, 창의 제목 부분
        //    colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        //    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
        //    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        //    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        //    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        //    // Title
        //    colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        //    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        //    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        //    // Menu
        //    colors[ImGuiCol_MenuBarBg] = ImVec4{ 1.f, 1.f, 1.f, 1.f };
        //}
        
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(WINDOW->GetGameDesc().hWnd);
    ImGui_ImplDX11_Init(DEVICE.Get(), CONTEXT.Get());


    // ImDockSpace push First
    AddWindows(makeSptr<ImDockSpace>(), "DockSpace");

    AddWindows(makeSptr<ImScene>(),     "Scene");
    AddWindows(makeSptr<ImInspector>(), "Inspector");
    AddWindows(makeSptr<ImProject>(),   "Project");
    AddWindows(makeSptr<ImConsole>(),   "Console");
    AddWindows(makeSptr<ImHierarchy>(), "Hierarchy");


    // 나중에 에디터용 카메라 추가




    JLOG_INIT("GUI Init Complete");
}

void ImGuiManager::RenderBegin()
{
    CONTEXT->OMSetRenderTargets(1, DX->GetBackBufferRTV().GetAddressOf(), DX->GetDSV().Get());

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::Update()
{
    for (auto& window : _windows)
    {
        window->Update();
    }
}

void ImGuiManager::RenderEnd()
{
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void ImGuiManager::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::Image(const wstring& name, ImVec2 size)
{
    if (ASSET->Get<Texture>(name) == nullptr)
    {
        ImGui::Image(reinterpret_cast<void*>(ASSET->Get<Texture>(L"prohibition")->GetSRV().Get()), size);
    }
    else
    {
		ImGui::Image(reinterpret_cast<void*>(ASSET->Get<Texture>(name)->GetSRV().Get()), size);
    }
}

void ImGuiManager::AddWindows(sptr<class ImWindow> window, string name)
{
    window->Init();
    window->SetName(name);

    _windows.push_back(window);
}

void ImGuiManager::GUI_Thread()
{
	std::lock_guard<std::mutex> lock(_mutex);

    while (_destroy)
    {
        RenderBegin();

        Update();

        RenderEnd();
    }
}

void ImGuiManager::Notify(sptr<GameObject> go)
{
    for (auto& window : _windows)
    {
        window->StateUpdate(go);
    }
}

void ImGuiManager::NotifyWindow(const string& name)
{
    GUI->SetFocusedWindow(name);
}
