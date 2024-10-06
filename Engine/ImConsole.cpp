#include "pch.h"
#include "ImConsole.h"

void ImConsole::Init()
{
}

void ImConsole::Update()
{
	ImGui::Begin("Console");
	IMFOCUS("Console");
	{
		auto& logs = JLOG->GetLogs();

		if (logs.empty() == true)
		{
			return;
		}

		if (ImGui::Button("Clear"))
		{
			JLOG->Clear();
		}
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();

		if (ImGui::Checkbox("Detail", &_showDetail))
		{
			_showDetail = true ? _showDetail : !_showDetail;
		}

		ImGui::SameLine();
		ImGui::Bullet();
		ImGui::Text("Logs: %d messages", logs.size());

		ImGui::SeparatorText("");

		ImGui::BeginChild("Log");
		if (copy == true)
		{
			ImGui::LogToClipboard();
		}

		for (const auto& log : logs)
		{
			switch (log.level)
			{
			case LogLevel::LOG_LEVEL_INIT:
				ImGui::PushStyleColor(ImGuiCol_Text, initLogColor);
				break;
			case LogLevel::LOG_LEVEL_INFO:
				ImGui::PushStyleColor(ImGuiCol_Text, infoLogColor);
				break;
			case LogLevel::LOG_LEVEL_WARNING:
				ImGui::PushStyleColor(ImGuiCol_Text, warningLogColor);
				break;
			case LogLevel::LOG_LEVEL_ERROR:
				ImGui::PushStyleColor(ImGuiCol_Text, errorLogColor);
				break;
			}

			if (_showDetail == true)
			{
				ImGui::Text("[%s] %s\n(%s:%d)", log.timeStamp.c_str(), log.message.c_str(), log.sourceFile.c_str(), log.lineNumber);
			}
			else
			{
				const char* simplePath = strrchr(log.sourceFile.c_str(), '\\') + 1;
				ImGui::Text("[%s] %s\n(%s:%d)", log.timeStamp.c_str(), log.message.c_str(), simplePath, log.lineNumber);
			}

			ImGui::PopStyleColor();
			ImGui::SeparatorText("");
		}

		if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::EndChild();
	}
	ImGui::End();
}
