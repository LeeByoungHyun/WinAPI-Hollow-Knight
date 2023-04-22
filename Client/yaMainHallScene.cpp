#include "yaMainHallScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaResourceManager.h"
#include "yaTime.h"
#include "yaGameObject.h"

#include "yaPlayer.h"
#include "yaCrawlid.h"
#include "yaBackBoard.h"
#include "GodBG.h"
#include "GroundCollider.h"
#include "LongPlatform.h"
#include "LongPlatformBackPixel.h"
#include "BossDoor.h"
#include "HPInterface.h"
#include "HPobject01.h"
#include "HPobject02.h"
#include "HPobject03.h"
#include "HPobject04.h"
#include "HPobject05.h"
#include "SoulUI.h"
#include "TestCollider.h"
#include "Fade.h"
#include "Spike.h"
#include "Platform01.h"
#include "Platform02.h"
#include "Platform03.h"

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
		//object::Instantiate<Crawlid>(Vector2(1400.0f, 1300.0f - 103.0f), eLayerType::Monster);
		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<BossDoor>(Vector2(1724.0f, 1300.0f), eLayerType::Object);
		object::Instantiate<LongPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Ground);
		//object::Instantiate<Platform01>(Vector2(1724.0f, 1100.0f), eLayerType::Ground);
		//object::Instantiate<Platform02>(Vector2(1324.0f, 1100.0f), eLayerType::Ground);
		//object::Instantiate<Platform03>(Vector2(1124.0f, 1100.0f), eLayerType::Ground);

		// test
		object::Instantiate<TestCollider>(Vector2(1724.0f, 1000.0f), eLayerType::Object);

		// 싱글톤을 이용하여 모든 씬에서 플레이어가 1개만 존재하도록 함
		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1400.0f, 1300.0f));

		// UI
		hpUI = ya::HPInterface::GetInstance();
		scene->AddGameObject(hpUI, eLayerType::UI);
		hpUI->Initialize();
		hpUI->SetType(eLayerType::UI);
		hp01 = ya::HPobject01::GetInstance();
		scene->AddGameObject(hp01, eLayerType::UI);
		hp01->Initialize();
		hp01->SetType(eLayerType::UI);
		hp02 = ya::HPobject02::GetInstance();
		scene->AddGameObject(hp02, eLayerType::UI);
		hp02->Initialize();
		hp02->SetType(eLayerType::UI);
		hp03 = ya::HPobject03::GetInstance();
		scene->AddGameObject(hp03, eLayerType::UI);
		hp03->Initialize();
		hp03->SetType(eLayerType::UI);
		hp04 = ya::HPobject04::GetInstance();
		scene->AddGameObject(hp04, eLayerType::UI);
		hp04->Initialize();
		hp04->SetType(eLayerType::UI);
		hp05 = ya::HPobject05::GetInstance();
		scene->AddGameObject(hp05, eLayerType::UI);
		hp05->Initialize();
		hp05->SetType(eLayerType::UI);
		soulUI = ya::SoulUI::GetInstance();
		scene->AddGameObject(soulUI, eLayerType::UI);
		soulUI->Initialize();
		soulUI->SetType(eLayerType::UI);
		fade = ya::Fade::GetInstance();
		scene->AddGameObject(fade, eLayerType::Fade);
		fade->Initialize();
		fade->SetType(eLayerType::Fade);
	}

	void MainHallScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		if (Input::GetKeyState(eKeyCode::M) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::FalseKnightBoss);
		}

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::HornetBoss);
		}

		if (Player::GetInstance()->GetPlayerState() == Player::ePlayerState::Death)
		{
			Player::GetInstance()->SetState(GameObject::eState::Active);
			fade->SetFadeState(Fade::eFadeState::FadeIn);
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

		CollisionManager::SetLayer(eLayerType::NeilEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Spike, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Object, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(800.0f);
		Camera::SetMaxX(2648.0f);
		Camera::SetMinY(1300.0f);
		Camera::SetMaxY(0.0f);
	}

	void MainHallScene::Exit()
	{
		Scene::Exit();
	}
}