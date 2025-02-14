#pragma once

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//	spdlog : 콘솔창에 로그찍고싶으면 이거써야됨
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////



#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define LOG_TRACE(...)		Log::TraceLog   (Log::GetLogger(), __VA_ARGS__);
#define LOG_INFO(...)		Log::InfoLog    (Log::GetLogger(), __VA_ARGS__);
#define LOG_WARN(...)		Log::WarnLog    (Log::GetLogger(), __VA_ARGS__);
#define LOG_ERROR(...)		Log::ErrorLog   (Log::GetLogger(), __VA_ARGS__);
#define LOG_CRITICAL(...)	Log::CriticalLog(Log::GetLogger(), __VA_ARGS__);

class Log final
{
	SINGLETON(Log);
private:
	sptr<spdlog::logger> mLogger;
public:
	inline static sptr<spdlog::logger>& GetLogger() { return LOG->mLogger; }
public:
	/*Log()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		mLogger = spdlog::stdout_color_mt("Client ");
		mLogger->set_level(spdlog::level::trace);
	}*/
	~Log()
	{
		mLogger.reset();
		spdlog::shutdown();
	}
public:
	void Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		mLogger = spdlog::stdout_color_mt("Client ");
		mLogger->set_level(spdlog::level::trace);
	}
public:
	template<class ...T>
	inline static void TraceLog(sptr<spdlog::logger> logger, T ... args)
	{
		logger->trace(Convert(args)...);
	}
	template<class ...T>
	inline static void InfoLog(sptr<spdlog::logger> logger, T ... args)
	{
		logger->info(Convert(args)...);
	}
	template<class ...T>
	inline static void WarnLog(sptr<spdlog::logger> logger, T ... args)
	{
		logger->warn(Convert(args)...);
	}
	template<class ...T>
	inline static void ErrorLog(sptr<spdlog::logger> logger, T ... args)
	{
		logger->error(Convert(args)...);
	}
	template<class ...T>
	inline static void CriticalLog(sptr<spdlog::logger> logger, T ... args)
	{
		logger->critical(Convert(args)...);
	}
private:
	template<class T>
	static auto Convert(T&& arg)
	{
		return std::forward<T>(arg);
	}
};

