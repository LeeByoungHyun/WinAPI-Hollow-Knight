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

		//void Release();


	private:
		HWND mHwnd;
		HDC mHdc;

		// 백버퍼
		HBITMAP mBackBuffer;
		HDC mBackHdc;

		// 해상도
		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}

