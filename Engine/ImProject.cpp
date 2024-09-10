#include "pch.h"
#include "ImProject.h"

void ImProject::Init()
{
}

void ImProject::Update()
{
	ImGui::Begin("Project"); IMFOCUS("Project");

    static f32 left_pane_width = 200.0f;   // �ʱ� ���� �г� �ʺ�
    f32 right_pane_min_width   = 50.0f;    // ������ �г� �ּ� �ʺ�
    f32 splitter_size          = 2.f;      // ���ø���(���)�� �β�

    // â�� �ʺ� ���
    f32 window_width = ImGui::GetContentRegionAvail().x;

    // ù ��° �г�
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

    // �г� ���̿� ������ ������ �ʵ��� ImGui::SameLine() ���� ������ 0���� ����
	ImGui::SameLine(0.f, 0.f);

    //// Splitter(���) ����
    ImGui::InvisibleButton("Splitter", ImVec2(splitter_size, -1.0f));

    // ���콺�� Splitter ���� ���� �� Ŀ�� ��� ����
    if (ImGui::IsItemHovered()) 
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW); // �¿� ȭ��ǥ Ŀ���� ����
    }
    
    // ���콺�� �巡���ϸ� �г� ũ�� ����
    if (ImGui::IsItemActive()) 
{
        left_pane_width += ImGui::GetIO().MouseDelta.x; // ���콺 �̵����� ���� ũ�� ����
    
        // �г� ũ�� ����
        if (left_pane_width < 50.0f) 
        {
            left_pane_width = 50.0f; // �ּ� ũ��
        }
        if (left_pane_width > window_width - right_pane_min_width)
        {
            left_pane_width = window_width - right_pane_min_width; // �ִ� ũ��
        }
    }
    
    ImGui::SameLine(0.0f, 0.0f); // �е��� 0���� ����

    // �� ��° �г�
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
			// Ȯ���� O
			//ImGui::Text("%s", file_path.filename().string().c_str());
			// Ȯ���� X
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
            // Ȯ���� O
            ImGui::Text("%s", file_path.filename().string().c_str());
            // Ȯ���� X
            //ImGui::Text("%s", file_path.stem().string().c_str());
        }
    }
}
