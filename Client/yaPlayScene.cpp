#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"


namespace ya
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		// 게임오브젝트 추가는 이곳에
		mPlayer = new Player();
		AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->SetName(L"Player");

		mBackBoard = new BackBoard();
		AddGameObject(mBackBoard, eLayerType::BG);
		mBackBoard->SetName(L"backboard");

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void PlayScene::Release()
	{
		Scene::Release();

	}

	void PlayScene::Enter()
	{

	}

	void PlayScene::Exit()
	{

	}
}