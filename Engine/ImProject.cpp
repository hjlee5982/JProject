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

        GUI->Image(L"folder");
        ImGui::SameLine();
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
        f32 path_height   = 35.f;

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

			GUI->Image(L"folder");
            ImGui::SameLine();
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
    f32 icon_size    = 80.f;
    f32 item_spacing = 10.f;
    f32 text_height  = ImGui::GetTextLineHeightWithSpacing();

    f32 max_name_width = icon_size;
    
    f32 max = ImGui::GetWindowContentRegionMax().x;
    f32 min = ImGui::GetWindowContentRegionMin().x;

    f32 window_visible = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
    i32 items_per_row  = static_cast<i32>(window_visible / (icon_size + item_spacing));
    i32 item_count     = 0;

    std::filesystem::path p(_selectedPath);

    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        const std::filesystem::path& file_path = entry.path();

        if (items_per_row != 0)
        {
            if (item_count > 0 && item_count % items_per_row != 0)
            {
                ImGui::SameLine();
            }
        }

        wstring ext = Utils::ExtractExtension(file_path.filename().wstring());

        ImGui::BeginGroup();
        {
            bool is_directory = std::filesystem::is_directory(file_path);

            if (is_directory == true)
            {
                GUI->Image(L"folder", ImVec2(icon_size, icon_size));
            }
            else
            {
				GUI->Image(file_path.stem().wstring(), ImVec2(icon_size, icon_size));
            }

            // ��� ����
            f32 text_width = ImGui::CalcTextSize(file_path.stem().string().c_str()).x;
            f32 cursor_x   = ImGui::GetCursorPosX();
            if (text_width < max_name_width)
            {
                ImGui::SetCursorPosX(cursor_x + (icon_size - text_width) * 0.5f);
            }

            // ���� �̸��� ��� ...���� ǥ��, ���콺 �ø��� Ǯ���� ǥ��
            if (text_width > max_name_width)
            {
                string truncated_name(file_path.stem().string().c_str());
                truncated_name = truncated_name.substr(0, 7) + "...";
                ImGui::TextWrapped("%s", truncated_name.c_str());

                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip(file_path.stem().string().c_str());
                }
            }
            else
            {
				ImGui::TextWrapped(file_path.stem().string().c_str());
            }
        }
        ImGui::EndGroup();
        item_count++;
    }
}
