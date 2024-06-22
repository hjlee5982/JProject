#include "pch.h"
#include "TimeManager.h"

//void TimeManager::Init()
//{
//	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFrequency));
//	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mPrevCount));
//}
//
//void TimeManager::Update()
//{
//	u64 currentCount;
//	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));
//
//	mDeltaTime = (currentCount - mPrevCount) / static_cast<float>(mFrequency);
//	mPrevCount = currentCount;
//
//	mFrameCount++;
//	mFrameTime += mDeltaTime;
//
//	if (mFrameTime > 1.f)
//	{
//		mFPS = static_cast<u32>(mFrameCount / mFrameTime);
//
//		mFrameTime  = 0.f;
//		mFrameCount = 0;
//	}
//}

void TimeManager::Init()
{
	
}

void TimeManager::Update()
{
	if (_isFirst == true)
	{
		_timePoint = std::chrono::steady_clock::now();
		_isFirst = false;
		return;
	}

	std::chrono::duration<f32> sec = std::chrono::steady_clock::now() - _timePoint;

	_deltaTime = sec.count();

	if (_deltaTime >= 0.0f)
	{
		_totalTime += _deltaTime;

		++_frameCount;

		_elapsed += _deltaTime;

		if (_elapsed >= 1.0f)
		{
			_FPS = _frameCount;
			_frameCount = 0;
			_elapsed = 0.0f;
		}
	}

	_timePoint = std::chrono::steady_clock::now();
}
