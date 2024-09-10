#include "pch.h"
#include "ImProject.h"

void ImProject::Init()
{
}

void ImProject::Update()
{
	ImGui::Begin("Project"); IMFOCUS("Project");

    static f32 left_pane_width = 200.0f;   // 초기 왼쪽 패널 너비
    f32 right_pane_min_width   = 50.0f;    // 오른쪽 패널 최소 너비
    f32 splitter_size          = 2.f;      // 스플리터(경계)의 두께

    // 창의 너비 계산
    f32 window_width = ImGui::GetContentRegionAvail().x;

    // 첫 번째 패널
    ImGui::BeginChild("Left Pane", ImVec2(left_pane_width, 0), true);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(-2, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 0));

        std::filesystem::path p("..\\Assets");

        GUI->Image(L"FolderIcon");
        if (ImGui::TreeNode("Assets"))
        {
            if (ImGui::IsItemToggledOpen() || ImGui::IsItemClicked())
            {
                _selectedPath = "..\\Assets";
            }
            RenderFileExplorer(p);
            ImGui::TreePop();
        }

        ImGui::PopStyleVar(2);

		//std::filesystem::path p("..\\Assets");
		//RenderFileExplorer(p);
    }
    ImGui::EndChild();

    // 패널 사이에 공간이 생기지 않도록 ImGui::SameLine() 전에 간격을 0으로 설정
	ImGui::SameLine(0.f, 0.f);

    //// Splitter(경계) 구현
    ImGui::InvisibleButton("Splitter", ImVec2(splitter_size, -1.0f));

    // 마우스가 Splitter 위에 있을 때 커서 모양 변경
    if (ImGui::IsItemHovered()) 
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW); // 좌우 화살표 커서로 변경
    }
    
    // 마우스를 드래그하면 패널 크기 조절
    if (ImGui::IsItemActive()) 
{
        left_pane_width += ImGui::GetIO().MouseDelta.x; // 마우스 이동량에 따라 크기 조절
    
        // 패널 크기 제한
        if (left_pane_width < 50.0f) 
        {
            left_pane_width = 50.0f; // 최소 크기
        }
        if (left_pane_width > window_width - right_pane_min_width)
        {
            left_pane_width = window_width - right_pane_min_width; // 최대 크기
        }
    }
    
    ImGui::SameLine(0.0f, 0.0f); // 패딩을 0으로 설정

    // 두 번째 패널
    ImGui::BeginChild("Right Pane", ImVec2(0, 0), true);
    {
        f32 window_width  = ImGui::GetContentRegionAvail().x;
        f32 window_height = ImGui::GetContentRegionAvail().y;
        f32 path_height   = 30.f;

        ImGui::BeginChild("Path", ImVec2(window_width, path_height), true);
        {
			ImGui::Text(_selectedPath.c_str());
        }
        ImGui::EndChild();

        ImGui::BeginChild("Explorer", ImVec2(window_width, window_height - path_height * 2.f * 1.12f), true);
        {
            RenderFolderItems();
        }
        ImGui::EndChild();

        ImGui::BeginChild("FileName", ImVec2(window_width, path_height), true);
        {
            ImGui::Text("FileName");
        }
        ImGui::EndChild();
    }
    ImGui::EndChild();
    
	ImGui::End();
}

void ImProject::RenderFileExplorer(const std::filesystem::path& path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		const std::filesystem::path& file_path = entry.path();

		bool is_directory = std::filesystem::is_directory(file_path);

		if (is_directory == true)
		{
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(-2, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 0));

			GUI->Image(L"FolderIcon");
			if (ImGui::TreeNode(file_path.filename().string().c_str()))
			{
                if (ImGui::IsItemToggledOpen() || ImGui::IsItemClicked())
                {
                    _selectedPath = file_path.string();
                }
				RenderFileExplorer(file_path);
				ImGui::TreePop();
			}

            ImGui::PopStyleVar(2);
		}
		else
		{
			// 확장자 O
			//ImGui::Text("%s", file_path.filename().string().c_str());
			// 확장자 X
			//ImGui::Text("%s", file_path.stem().string().c_str());
		}
	}
}

void ImProject::RenderFolderItems()
{
    std::filesystem::path p(_selectedPath);

    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        const std::filesystem::path& file_path = entry.path();

        bool is_directory = std::filesystem::is_directory(file_path);

        if (is_directory == true)
        {
            
        }
        else
        {
            // 확장자 O
            ImGui::Text("%s", file_path.filename().string().c_str());
            // 확장자 X
            //ImGui::Text("%s", file_path.stem().string().c_str());
        }
    }
}
