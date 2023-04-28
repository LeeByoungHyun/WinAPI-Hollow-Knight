#include "EndingScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaObject.h"
#include "yaSound.h"
#include "yaResourceManager.h"
#include "yaApplication.h"

extern ya::Application application;

namespace ya
{
	EndingScene::EndingScene()
	{

	}

	EndingScene::~EndingScene()
	{

	}

	void EndingScene::Initialize()
	{

		Scene::Initialize();
		Scene* scene = SceneManager::GetActiveScene();

		//SetWindowPos(videoHwnd, HWND_BOTTOM, 0, 0, 1600, 900, SWP_NOMOVE | SWP_NOZORDER);
		HWND hWnd = GetActiveWindow();

		videoHwnd = MCIWndCreate(hWnd
			, NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR
			, L"..\\Resources\\Video\\MaskShatter.wmv");
		MoveWindow(videoHwnd, 0, 0, 1600, 900, NULL);

	}

	void EndingScene::Update()
	{
		Scene::Update();

		if (flag == false)
		{
			MCIWndPlay(videoHwnd);
			flag = true;
		}
	}

	void EndingScene::Render(HDC hdc)
	{
		//Scene::Render(hdc);
	}

	void EndingScene::Release()
	{
		Scene::Release();
	}

	void EndingScene::Enter()
	{
		
	}

	void EndingScene::Exit()
	{
		
	}
}