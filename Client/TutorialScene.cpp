#include "TutorialScene.h"
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
#include "BG_Large.h"
#include "HPInterface.h"
#include "HPobject01.h"
#include "HPobject02.h"
#include "HPobject03.h"
#include "HPobject04.h"
#include "HPobject05.h"
#include "SoulUI.h"
#include "Fade.h"
#include "Spike.h"
#include "Pillar_Large.h"
#include "Platform01.h"
#include "Platform02.h"
#include "Platform03.h"
#include "Spike_Large.h"
#include "Wall_Middle_Left.h"
#include "Wall_Middle_Right.h"
#include "LongPlatform.h"
#include "Zote_Statue.h"

namespace ya
{
	TutorialScene::TutorialScene()
	{

	}

	TutorialScene::~TutorialScene()
	{

	}

	void TutorialScene::Initialize()
	{
		Scene::Initialize();
		Scene* scene = SceneManager::GetActiveScene();

		// 게임오브젝트 추가는 이곳에	
		object::Instantiate<BG_Large>(Vector2(2700.0f, 2700.0f), eLayerType::BG);
		object::Instantiate<Pillar_Large>(Vector2(145.0f, 2700.0f), eLayerType::Object);
		object::Instantiate<Spike_Large>(Vector2(2700.0f, 2700.0f), eLayerType::Spike);
		object::Instantiate<Platform03>(Vector2(600.0f, 2200.0f), eLayerType::Platform);
		object::Instantiate<Platform02>(Vector2(1100.0f, 2200.0f), eLayerType::Platform);
		object::Instantiate<Platform02>(Vector2(1550.0f, 2200.0f), eLayerType::Platform);
		object::Instantiate<Platform02>(Vector2(2000.0f, 2200.0f), eLayerType::Platform);
		object::Instantiate<Platform03>(Vector2(2900.0f, 2200.0f), eLayerType::Platform);
		object::Instantiate<Platform03>(Vector2(3800.0f, 2200.0f), eLayerType::Platform);
		object::Instantiate<Wall_Middle_Right>(Vector2(4040.0f, 2100.0f), eLayerType::Object);
		object::Instantiate<Wall_Middle_Left>(Vector2(3560.0f, 1800.0f), eLayerType::Object);
		object::Instantiate<LongPlatform>(Vector2(4750.0f, 1630.0f), eLayerType::Platform);
		object::Instantiate<Pillar_Large>(Vector2(5400.0f - 145.0f, 2700.0f), eLayerType::Platform);
		object::Instantiate<Zote_Statue>(Vector2(4750.0f, 1630.0f - 99.0f), eLayerType::Object);
		//object::Instantiate<Zote_Statue>(Vector2(600.0f, 2200.0f - 100.0f), eLayerType::Object);

		victorySound = ResourceManager::Load<Sound>(L"VictorySound", L"..\\Resources\\Sound\\Hallownest_Call.wav");

		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);

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

	void TutorialScene::Update()
	{
		Scene::Update();

		Camera::SetMaxX(4500.0f);

		if (Player::GetInstance()->GetPlayerState() == Player::ePlayerState::Death)
		{
			Player::GetInstance()->SetState(GameObject::eState::Active);
			fade->SetFadeState(Fade::eFadeState::FadeIn);
		}

		if (Fade::GetInstance()->GetFadeState() == Fade::eFadeState::Neutral && startFlag == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 3.0f)
			{
				mPlayer->SetPlayerState(Player::ePlayerState::Idle);
				startFlag = true;
				mTime = 0.0f;
			}
		}
	}

	void TutorialScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void TutorialScene::Release()
	{
		Scene::Release();
	}

	void TutorialScene::Destroy()
	{
		Scene::Destroy();
	}

	void TutorialScene::Enter()
	{
		Scene::Enter();

		CollisionManager::SetLayer(eLayerType::NeilEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Spike, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Object, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Platform, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(900.0f);
		Camera::SetMaxX(5000.0f);
		Camera::SetMinY(2250.0f);
		Camera::SetMaxY(0.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(500.0f, 2100.0f));
	}

	void TutorialScene::Exit()
	{
		Scene::Exit();
	}
}