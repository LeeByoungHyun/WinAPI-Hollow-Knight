#include "yaTime.h"

namespace ya
{
	double Time::mDeltaTime = 0.0l;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initialize()
	{
		// CPU ���� ������ ��������
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷� ���۽� ������
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		// ���� ������ ����
		QueryPerformanceCounter(&mCurFrequency);

		double diffenceFrequancy = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = diffenceFrequancy / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{

	}
}