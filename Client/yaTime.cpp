#include "yaTime.h"

namespace ya
{
	double Time::mDeltaTime = 0.0l;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initialize()
	{
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램 시작시 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		// 현재 진동수 측정
		QueryPerformanceCounter(&mCurFrequency);

		double diffenceFrequancy = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = diffenceFrequancy / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{

	}
}