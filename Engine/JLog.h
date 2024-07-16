#pragma once

enum class LogLevel
{
	LOG_LEVEL_INIT,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
};

#ifdef _DEBUG
#define JLOG_INIT(...)    JLOG->GetInstance()->AddLog(LogLevel::LOG_LEVEL_INIT,    __FILE__, __LINE__, __VA_ARGS__);
#define JLOG_INFO(...)    JLOG->GetInstance()->AddLog(LogLevel::LOG_LEVEL_INFO,    __FILE__, __LINE__, __VA_ARGS__);
#define JLOG_WARNING(...) JLOG->GetInstance()->AddLog(LogLevel::LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__);
#define JLOG_ERROR(...)   JLOG->GetInstance()->AddLog(LogLevel::LOG_LEVEL_ERROR,   __FILE__, __LINE__, __VA_ARGS__);
#else
#define JLOG_INIT(...)    return;
#define JLOG_INFO(...)    return;
#define JLOG_WARNING(...) return;
#define JLOG_ERROR(...)   return;
#endif

class JLog
{
	DECLARE_SINGLETON(JLog);
public:
	struct LogMessage
	{
		LogLevel level;
		string   message;
		string   timeStamp;
		string   sourceFile;
		i32      lineNumber;
	};
public:
	void Init()
	{
		Clear();

		JLOG_INIT("Program Start");
		JLOG_INIT("Logger Init Complete");
	}
public:
	void Clear()
	{
		_messages.clear();
	}
	void AddLog(LogLevel level, string sourceFile, i32 lineNunber, const char* fmt, ...) IM_FMTARGS(3)
	{
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, sizeof(buf), fmt, args);
		va_end(args);
		buf[sizeof(buf) - 1] = 0;

		auto now       = chrono::system_clock::now();
		auto in_time_t = chrono::system_clock::to_time_t(now);

		const tm* localtime = std::localtime(&in_time_t);

		stringstream ss;
		ss << std::put_time(localtime, "%X");
		// 인자 정보 : https://en.cppreference.com/w/cpp/io/manip/put_time

		_messages.push_back({ level, buf, ss.str(), sourceFile, lineNunber });
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

		ImGui::Text("Logs: %d messages", _messages.size());

		ImGui::SeparatorText("");

		ImGui::BeginChild("Log");
		if (copy == true)
		{
			ImGui::LogToClipboard();
		}

		for (const auto& msg : _messages)
		{
			switch (msg.level)
			{
			case LogLevel::LOG_LEVEL_INIT:
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
				break;
			case LogLevel::LOG_LEVEL_INFO:
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
				break;
			case LogLevel::LOG_LEVEL_WARNING:
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
				break;
			case LogLevel::LOG_LEVEL_ERROR:
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
				break;
			}

			//ImGui::TextUnformatted(msg.message.c_str());
			ImGui::Text("[%s] %s\n(%s:%d)", msg.timeStamp.c_str(), msg.message.c_str(), msg.sourceFile.c_str(), msg.lineNumber);
			ImGui::PopStyleColor();
			ImGui::SeparatorText("");
		}

		if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::EndChild();
		ImGui::End();
	}
private:
	vector<LogMessage> _messages;
	bool _autoScroll = true;
};




// Only Text, No Color

//class JLog
//{
//	DECLARE_SINGLETON(JLog);
//public:
//	void Init()
//	{
//		Clear();
//	}
//public:
//	void Clear()
//	{
//		_buffer.clear();
//	}
//	void AddLog(const char* fmt, ...) IM_FMTARGS(2)
//	{
//		va_list args;
//		va_start(args, fmt);
//		AddLog(fmt, args);
//		va_end(args);
//	}
//	void AddLog(const char* fmt, va_list args)
//	{
//		i32 old_size = _buffer.size();
//		_buffer.appendfv(fmt, args);
//
//		for (i32 new_size = _buffer.size(); old_size < new_size; old_size++)
//		{
//			if (_buffer[old_size] == '\n')
//			{
//				_lineOffsets.push_back(old_size + 1);
//			}
//		}
//	}
//	void Draw(const char* title = "Log", bool* p_open = nullptr)
//	{
//		if (!ImGui::Begin(title, p_open))
//		{
//			ImGui::End();
//			return;
//		}
//
//		if (ImGui::Button("Clear"))
//		{
//			Clear();
//		}
//		ImGui::SameLine();
//		bool copy = ImGui::Button("Copy");
//		ImGui::SameLine();
//
//		ImGui::Text("Logs: %d lines", _lineOffsets.Size);
//
//		ImGui::Separator();
//
//		ImGui::BeginChild("Log");
//		if (copy == true)
//		{
//			ImGui::LogToClipboard();
//		}
//
//		ImGui::TextUnformatted(_buffer.begin());
//
//		if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
//		{
//			ImGui::SetScrollHereY(1.0f);
//		}
//
//		ImGui::EndChild();
//		ImGui::End();
//	}
//private:
//	ImGuiTextBuffer _buffer;
//	ImVector<i32>   _lineOffsets;
//	bool            _autoScroll = true;
//};
