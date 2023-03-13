#include "yaMainHallScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaPlayer.h"
#include "yaCrawlid.h"
#include "yaBackBoard.h"
#include "yaGrimRoomBG.h"

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

		// 게임오브젝트 추가는 이곳에	
		Player* mPlayer = object::Instantiate<Player>(Vector2(600.0f, 800.0f), eLayerType::Player);
		Crawlid* c1 = object::Instantiate<Crawlid>(Vector2(400.0f, 800.0f), eLayerType::Monster);
		Crawlid* c2 = object::Instantiate<Crawlid>(Vector2(800.0f, 800.0f), eLayerType::Monster);
		Crawlid* c3 = object::Instantiate<Crawlid>(Vector2(950.0f, 800.0f), eLayerType::Monster);
		Crawlid* c4 = object::Instantiate<Crawlid>(Vector2(1100.0f, 800.0f), eLayerType::Monster);
		object::Instantiate<GrimRoomBG>(eLayerType::BG);

		//Camera::SetTarget(mPlayer);
	}

	void MainHallScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Boss);
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

		Crawlid* c1 = object::Instantiate<Crawlid>(Vector2(400.0f, 800.0f), eLayerType::Monster);
		Crawlid* c2 = object::Instantiate<Crawlid>(Vector2(800.0f, 800.0f), eLayerType::Monster);
		Crawlid* c3 = object::Instantiate<Crawlid>(Vector2(950.0f, 800.0f), eLayerType::Monster);
		Crawlid* c4 = object::Instantiate<Crawlid>(Vector2(1100.0f, 800.0f), eLayerType::Monster);

		CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}

	void MainHallScene::Exit()
	{
		Scene::Exit();
	}
}