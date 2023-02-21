#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"

namespace ya
{
	Application::Application()
	{
		mHwnd = NULL;
		mHdc = NULL;
	}

	Application::~Application()
	{

	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);

		Input::Initialize();
		Time::Initialize();
		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		Input::Render(mHdc);
		Time::Render(mHdc);

		Rectangle(mHdc, -1, -1, 1601, 901);
		SceneManager::Render(mHdc);
	}
}
