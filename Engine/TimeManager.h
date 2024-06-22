#pragma once

//class TimeManager
//{
//	DECLARE_SINGLETON(TimeManager);
//public:
//	void Init();
//public:
//	u32 GetFPS() 
//	{
//		return mFPS;
//	}
////***************************************//
//public:
//	void Update();
//public:
//	f32 GetDeltaTime()
//	{
//		return mDeltaTime; 
//	}
//private:
//	f32 mDeltaTime = 0.f;
//	u64	mFrequency = 0;
//	u64	mPrevCount = 0;
//private:
//	f32 mFrameTime = 0.f;
//	u32	mFrameCount = 0;
//	u32	mFPS = 0;
//};

class TimeManager
{
public:
	DECLARE_SINGLETON(TimeManager);
public:
	void Init();
	void Update();
public:
	f32 GetDeltaTime()
	{
		return _deltaTime;
	}
	u32 GetFPS()
	{
		return _FPS;
	}
private:
	std::chrono::steady_clock::time_point _timePoint;
	bool _isFirst   = true;
private:
	f32 _totalTime  = 0.0f;
	f32 _deltaTime  = 0.0f;
	f32 _elapsed    = 0.0f;
private:
	u32 _FPS        = 0;
	u32 _frameCount = 0;
};

