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

		Vector2 mPos;
	};
}

