#include "yaBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"

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
		Scene::Initialize();

		// ���ӿ�����Ʈ �߰��� �̰���

		//object::Instantiate<Player>(Vector2(800.0f, 800.0f), eLayerType::Player);
		object::Instantiate<GrimRoomBG>(eLayerType::BG);
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