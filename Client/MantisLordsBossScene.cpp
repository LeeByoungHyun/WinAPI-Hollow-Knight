#include "MantisLordsBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaGrimRoomBG.h"
#include "MantisLords.h"

namespace ya
{
	MantisLordsBossScene::MantisLordsBossScene()
	{

	}

	MantisLordsBossScene::~MantisLordsBossScene()
	{

	}

	void MantisLordsBossScene::Initialize()
	{
		Scene::Initialize();

		// 게임오브젝트 추가는 이곳에
		object::Instantiate<Player>(Vector2(800.0f, 800.0f), eLayerType::Player);
		object::Instantiate<GrimRoomBG>(eLayerType::BG);

		object::Instantiate<MantisLords>(Vector2(800.0f, 400.0f), eLayerType::Monster);
		object::Instantiate<MantisLords>(Vector2(500.0f, 400.0f), eLayerType::Monster);
		object::Instantiate<MantisLords>(Vector2(1100.0f, 400.0f), eLayerType::Monster);
	}

	void MantisLordsBossScene::Update()
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

	void MantisLordsBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void MantisLordsBossScene::Release()
	{
		Scene::Release();
	}

	void MantisLordsBossScene::Enter()
	{
		Scene::Enter();
	}

	void MantisLordsBossScene::Exit()
	{
		Scene::Exit();
	}
}