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
		// ���ӿ�����Ʈ �߰��� �̰���
		mPlayer = new Player();
		AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->SetName(L"Player");
		mPlayer->SetPos({ 800.0f, 700.0f });

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

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
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
		Scene::Enter();
	}

	void BossScene::Exit()
	{
		Scene::Exit();
	}
}