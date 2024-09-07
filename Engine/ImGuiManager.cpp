#include "pch.h"
#include "ImGuiManager.h"
#include "ImWindow.h"
#include "ImScene.h"
#include "ImInspector.h"
#include "ImProject.h"
#include "ImConsole.h"
#include "Imhierarchy.h"

void ImGuiManager::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.Fonts->AddFontFromFileTTF("../Resources/Font/Consolas.ttf", 14.0f);

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(WINDOW->GetGameDesc().hWnd);
    ImGui_ImplDX11_Init(DEVICE.Get(), CONTEXT.Get());


    _windows.push_back(makeSptr<ImScene>());
    _windows.push_back(makeSptr<ImInspector>());
    _windows.push_back(makeSptr<ImProject>());
    _windows.push_back(makeSptr<ImConsole>());
    _windows.push_back(makeSptr<Imhierarchy>());

    for (auto& window : _windows)
    {
        window->Init();
    }

    JLOG_INIT("GUI Init Complete");
}

void ImGuiManager::RenderBegin()
{
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    // DockingSpace
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockingSpace", nullptr, window_flags);
    ImGui::PopStyleVar(1);
    ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu1"))
        {
            ImGui::MenuItem("Item1");
            ImGui::MenuItem("Item2");
            ImGui::MenuItem("Item3");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Menu2"))
        {
            ImGui::MenuItem("Item4");
            ImGui::MenuItem("Item5");
            ImGui::MenuItem("Item6");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Menu3"))
        {
            ImGui::MenuItem("Item7");
            ImGui::MenuItem("Item8");
            ImGui::MenuItem("Item9");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Menu4"))
        {
            ImGui::MenuItem("Item10");
            ImGui::MenuItem("Item20");
            ImGui::MenuItem("Item30");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Menu5"))
        {
            ImGui::MenuItem("Item100");
            ImGui::MenuItem("Item200");
            ImGui::MenuItem("Item300");
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
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
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Rendering
    ImGui::Render();
    const f32 color[4] = { 0.f, 0.f, 0.f, 0.f };
    CONTEXT->OMSetRenderTargets(1, DX->GetRenderTargetView().GetAddressOf(), nullptr);
    CONTEXT->ClearRenderTargetView(DX->GetRenderTargetView().Get(), color);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
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

void ImGuiManager::Notify(sptr<GameObject> go)
{
    for (auto& window : _windows)
    {
        window->StateUpdate(go);
    }
}
