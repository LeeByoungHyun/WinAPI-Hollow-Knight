#include "MantisLordsBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCollisionManager.h"

#include "yaPlayer.h"
#include "GodBG.h"
#include "MantisLords.h"
#include "yaCrawlid.h"
#include "GroundCollider.h"

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
		Scene* scene = SceneManager::GetActiveScene();

		// ���ӿ�����Ʈ �߰��� �̰���
		//object::Instantiate<Player>(Vector2(800.0f, 800.0f), eLayerType::Player);
		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<MantisLords>(Vector2(800.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<MantisLords>(Vector2(500.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<MantisLords>(Vector2(1100.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<GroundCollider>(Vector2(-100.0f, 1500.0f), eLayerType::Ground);

		// �̱����� �̿��Ͽ� ��� ������ �÷��̾ 1���� �����ϵ��� ��
		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);
		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(600.0f, 1300.0f));
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

		CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(600.0f, 1500.0f));
	}

	void MantisLordsBossScene::Exit()
	{
		Scene::Exit();
	}
}