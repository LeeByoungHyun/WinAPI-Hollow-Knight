#include "yaMainHallScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaResourceManager.h"

#include "yaPlayer.h"
#include "yaCrawlid.h"
#include "yaBackBoard.h"
#include "yaGrimRoomBG.h"
#include "GroundCollider.h"

namespace ya
{
	MainHallScene::MainHallScene()
	{

	}

	MainHallScene::~MainHallScene()
	{

	}

	void MainHallScene::Initialize()
	{
		Scene::Initialize();

		Scene* scene = SceneManager::GetActiveScene();

		// 게임오브젝트 추가는 이곳에	
		object::Instantiate<Crawlid>(Vector2(400.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<Crawlid>(Vector2(800.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<Crawlid>(Vector2(950.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<Crawlid>(Vector2(1100.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<GrimRoomBG>(Vector2(800.0f, 870.0f), eLayerType::BG);
		object::Instantiate<GroundCollider>(Vector2(-100.0f, 800.0f), eLayerType::Ground);

		// 싱글톤을 이용하여 모든 씬에서 플레이어가 1개만 존재하도록 함
		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);
		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(600.0f, 800.0f));

		Camera::SetTarget(mPlayer);
	}

	void MainHallScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::MantisLordsBoss);
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
	}

	void MainHallScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void MainHallScene::Release()
	{
		Scene::Release();
	}

	void MainHallScene::Destroy()
	{
		Scene::Destroy();
	}

	void MainHallScene::Enter()
	{
		Scene::Enter();

		object::Instantiate<Crawlid>(Vector2(400.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<Crawlid>(Vector2(800.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<Crawlid>(Vector2(950.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<Crawlid>(Vector2(1100.0f, 800.0f), eLayerType::Monster);

		CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

	}

	void MainHallScene::Exit()
	{
		Scene::Exit();
	}
}