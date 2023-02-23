#include "yaPlayScene.h"
#include "yaCuphead.h"
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
		mCuphead = new Cuphead();
		AddGameObject(mCuphead, eLayerType::Player);
		mCuphead->SetName(L"Player");

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