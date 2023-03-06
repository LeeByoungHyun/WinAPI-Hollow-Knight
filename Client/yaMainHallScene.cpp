#include "yaMainHallScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaBackBoard.h"
#include "yaTransform.h"
#include "yaCrawlid.h"
#include "yaCollisionManager.h"

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
		// 게임오브젝트 추가는 이곳에
		Player* mPlayer = new Player();
		AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->SetName(L"Player");
		mPlayer->GetComponent<Transform>()->SetPos( { 600.0f, 800.0f } );

		Crawlid* mCrawlid = new Crawlid();
		AddGameObject(mCrawlid, eLayerType::Monster);
		mCrawlid->SetName(L"Crawlid");
		mCrawlid->GetComponent<Transform>()->SetPos({ 800.0f, 800.0f });

		Backboard* mBackboard = new Backboard();
		AddGameObject(mBackboard, eLayerType::BG);
		mBackboard->SetName(L"backboard");

		CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initialize();
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

	void MainHallScene::Enter()
	{
		Scene::Enter();
	}

	void MainHallScene::Exit()
	{
		Scene::Exit();
	}
}