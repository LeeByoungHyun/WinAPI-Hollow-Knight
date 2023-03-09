#pragma once
#include "yamyamEngine.h"

namespace ya
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND mHwnd);
		void Run();

		void Update();
		void Render();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void Clear();

	private:
		HWND mHwnd;
		HDC mHdc;

		// �����
		HBITMAP mBackBuffer;
		HDC mBackHdc;

		// �ػ�
		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}

