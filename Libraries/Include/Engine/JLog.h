#pragma once

#define JLOG_INFO(...) JLOG->GetInstance()->AddLog(__VA_ARGS__);

class JLog
{
	DECLARE_SINGLETON(JLog);
public:
	void Init()
	{
		Clear();

	}
public:
	void Clear()
	{
		_buffer.clear();
	}
	void AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		va_list args;
		va_start(args, fmt);
		AddLog(fmt, args);
		va_end(args);
	}
	void AddLog(const char* fmt, va_list args)
	{
		i32 old_size = _buffer.size();
		_buffer.appendfv(fmt, args);

		for (i32 new_size = _buffer.size(); old_size < new_size; old_size++)
		{
			if (_buffer[old_size] == '\n')
			{
				_lineOffsets.push_back(old_size + 1);
			}
		}
	}
	void Draw(const char* title = "Log", bool* p_open = nullptr)
	{
		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		if (ImGui::Button("Clear"))
		{
			Clear();
		}
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();

		ImGui::Text("Logs: %d lines", _lineOffsets.Size);

		ImGui::Separator();

		ImGui::BeginChild("Log");
		if (copy == true)
		{
			ImGui::LogToClipboard();
		}

		ImGui::TextUnformatted(_buffer.begin());

		if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::EndChild();
		ImGui::End();
	}
private:
	ImGuiTextBuffer _buffer;
	ImVector<i32>   _lineOffsets;
	bool            _autoScroll = true;
};

