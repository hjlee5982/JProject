#include "pch.h"
#include "ImDockSpace.h"

void ImDockSpace::Init()
{
}

void ImDockSpace::Update()
{
    DockSpaceBegin();
    {
        if (ImGui::BeginMenuBar())
        {
            //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 1.f));
            if (ImGui::BeginMenu("File"))
            {
                //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

                ImGui::MenuItem("Load Scene");
                if (ImGui::MenuItem("Save Scene"))
                {
                    SCENE->SaveScene();
                    //JLOG_INFO("Save Scene Complete");
                }
                //ImGui::PopStyleColor();
                ImGui::EndMenu();
            }
            //ImGui::PopStyleColor();
            ImGui::EndMenuBar();
        }
    }
    DockSpaceEnd();
}

void ImDockSpace::DockSpaceBegin()
{
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
}

void ImDockSpace::DockSpaceEnd()
{
    ImGui::End();
}
