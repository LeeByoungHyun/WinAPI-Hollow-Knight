#include "yaBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"


namespace ya
{
	BossScene::BossScene()
	{

	}

	BossScene::~BossScene()
	{

	}

	void BossScene::Initialize()
	{
		// 게임오브젝트 추가는 이곳에
		mPlayer = new Player();
		AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->SetName(L"Player");

		mGrimRoomBG = new GrimRoomBG();
		AddGameObject(mGrimRoomBG, eLayerType::BG);
		mGrimRoomBG->SetName(L"grimRoomBG");

		Scene::Initialize();
	}

	void BossScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::MainHall);
		}
	}

	void BossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void BossScene::Release()
	{
		Scene::Release();

	}

	void BossScene::Enter()
	{

	}

	void BossScene::Exit()
	{

	}
}