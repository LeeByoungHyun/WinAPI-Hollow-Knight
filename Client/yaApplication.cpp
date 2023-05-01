#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaSoundManager.h"

namespace ya
{
	static bool colliderRender = false;

	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
		// mHwnd = NULL;
		// mHdc = NULL;
	}

	Application::~Application()
	{
		//SceneManager::Release();
		//Time::Release();
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);

		ShowCursor(false);

		// 해상도 설정
		mWidth = 1600;
		mHeight = 900;

		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경 및 출력 설정
		SetWindowPos(mHwnd, nullptr, 100, 50, rect.right - rect.left, rect.bottom - rect.top, 0);
		ShowWindow(mHwnd, true);

		// 백버퍼 생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHdc = CreateCompatibleDC(mHdc);
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(defaultBitmap);

		Input::Initialize();
		Time::Initialize();
		SoundManager::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
		SceneManager::Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		Camera::Update();
		SceneManager::Update();
		CollisionManager::Update();

		if (Input::GetKeyState(eKeyCode::R) == eKeyState::Down)
		{
			if (colliderRender == true)
				colliderRender = false;
			else
				colliderRender = true;
		}
	}

	void Application::Render()
	{
		if (backBufferFlag == true)
		{
			// 백버퍼에서 랜더링 작업
			Rectangle(mBackHdc, -1, -1, 1601, 901);

			Input::Render(mBackHdc);
			Time::Render(mBackHdc);
			SceneManager::Render(mBackHdc);

			// 백버퍼에 있는 그림을 원본버퍼에 그려준다
			BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
		}
		else
		{
			Input::Render(mHdc);
			Time::Render(mHdc);
			SceneManager::Render(mHdc);
		}
		
	}

	void Application::Clear()
	{

	}
}
