#include "FalseKnightBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaTime.h"
#include "yaResourceManager.h"
#include "yaSound.h"

#include "yaPlayer.h"
#include "FalseKnight.h"
#include "FalseKnightManager.h"
#include "GodBG.h"
#include "FalseKnightPlatform.h"
#include "FalseBarrel.h"
#include "HPInterface.h"
#include "HPobject01.h"
#include "HPobject02.h"
#include "HPobject03.h"
#include "HPobject04.h"
#include "HPobject05.h"
#include "HornetWallLeft.h"
#include "HornetWallRight.h"
#include "SoulUI.h"
#include "Fade.h"
#include "FalseObject01.h"
#include "FalseObject02.h"
#include "Egg_01.h"
#include "Egg_02.h"
#include "Egg_03.h"

namespace ya
{
	FalseKnightBossScene::FalseKnightBossScene()
	{

	}

	FalseKnightBossScene::~FalseKnightBossScene()
	{

	}

	void FalseKnightBossScene::Initialize()
	{
		Scene::Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		srand((unsigned int)time(NULL));

		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<FalseKnightPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Platform);
		object::Instantiate<HornetWallLeft>(Vector2(1724.0f - 991.0f, 1300.0f), eLayerType::Wall);
		object::Instantiate<HornetWallRight>(Vector2(1724.0f + 891.0f, 1300.0f), eLayerType::Wall);

		object::Instantiate<FalseObject01>(Vector2(1350.0f, 1300.0f - 140.0f), eLayerType::BGObject);
		object::Instantiate<FalseObject01>(Vector2(1950.0f, 1300.0f - 140.0f), eLayerType::BGObject);
		object::Instantiate<FalseObject02>(Vector2(1050.0f, 1300.0f - 140.0f), eLayerType::BGObject);
		object::Instantiate<FalseObject02>(Vector2(1650.0f, 1300.0f - 140.0f), eLayerType::BGObject);
		object::Instantiate<FalseObject02>(Vector2(2250.0f, 1300.0f - 140.0f), eLayerType::BGObject);
		object::Instantiate<Egg_01>(Vector2(950.0f, 1300.0f - 50.0f), eLayerType::BGObject);
		object::Instantiate<Egg_02>(Vector2(880.0f, 1300.0f - 40.0f), eLayerType::BGObject);
		object::Instantiate<Egg_03>(Vector2(1180.0f, 1300.0f - 40.0f), eLayerType::BGObject);
		object::Instantiate<Egg_01>(Vector2(1510.0f, 1300.0f), eLayerType::BGObject);
		object::Instantiate<Egg_01>(Vector2(2050.0f, 1300.0f - 50.0f), eLayerType::BGObject);
		object::Instantiate<Egg_02>(Vector2(1980.0f, 1300.0f - 40.0f), eLayerType::BGObject);
		object::Instantiate<Egg_03>(Vector2(1740.0f, 1300.0f - 30.0f), eLayerType::BGObject);
		object::Instantiate<Egg_01>(Vector2(2380.0f, 1300.0f - 50.0f), eLayerType::BGObject);
		object::Instantiate<Egg_02>(Vector2(2300.0f, 1300.0f - 40.0f), eLayerType::BGObject);


		mFalseManager = object::Instantiate<FalseKnightManager>(eLayerType::Manager);
		mFalseKnight = ya::FalseKnight::GetInstance();
		scene->AddGameObject(mFalseKnight, eLayerType::FalseKnight);
		mFalseKnight->Initialize();
		mFalseKnight->SetType(eLayerType::FalseKnight);

		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);

		falseBossTheme = ResourceManager::Load<Sound>(L"falseKnightTheme", L"..\\Resources\\Sound\\False Knight\\Boss Battle 1.wav");
		victorySound = ResourceManager::Load<Sound>(L"VictorySound", L"..\\Resources\\Sound\\Hallownest_Call.wav");

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

	void FalseKnightBossScene::Update()
	{
		Scene::Update();

		if (mFalseKnight->GetDeathSoundCheckFlag() == true)
		{
			falseBossTheme->Stop(true);
		}

		if (mFalseManager->GetPhaseState() == FalseKnightManager::ePhaseState::RageAttack)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 0.3)
			{
				int posX = rand() % 1600;
				object::Instantiate<FalseBarrel>(Vector2(1724.0f - 1000.0f + posX, 200.0f), eLayerType::Monster);
				mTime = 0.0f;
			}
		}

		if (Fade::GetInstance()->GetFadeState() == Fade::eFadeState::Neutral && startFlag == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 3.0f)
			{
				falseBossTheme->Play(true);
				mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Idle);
				startFlag = true;
				mTime = 0.0f;
			}
		}

		// 보스가 죽으면 fadeout하면서 다음 씬으로
		if (mFalseKnight->GetDeathFlag() == true)
		{
			mTime += Time::DeltaTime();

			if (mTime >= 3.0f && flag == false)
			{
				Fade::GetInstance()->SetFadeColor(Fade::eColor::White);
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeOut);
				victorySound->Play(false);
				flag = true;
			}
			if (mTime >= 8.0f && flag2 == false)
			{
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeIn);
				mFalseKnight->Reset();
				mFalseManager->Reset();
				SceneManager::LoadScene(eSceneType::HornetBoss);
				mTime = 0.0f;
				flag2 = true;
			}
		}

		if (mPlayer->GetPlayerState() == Player::ePlayerState::Skull && fade->GetAlpha() >= 255)
		{
			mFalseKnight->Reset();
			mFalseManager->Reset();
			SceneManager::LoadScene(eSceneType::Tutorial);
			Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeIn);
			mPlayer->SetPlayerState(Player::ePlayerState::WakeUp);
			mPlayer->SetHP(5);
			hpUI->initializeHP();
			
		}
	}

	void FalseKnightBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void FalseKnightBossScene::Release()
	{
		Scene::Release();
	}

	void FalseKnightBossScene::Enter()
	{
		Scene::Enter();

		CollisionManager::SetLayer(eLayerType::NeilEffect, eLayerType::FalseKnight, true);
		CollisionManager::SetLayer(eLayerType::SpellEffect, eLayerType::FalseKnight, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::FalseKnight, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Platform, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Platform, true);
		CollisionManager::SetLayer(eLayerType::FalseKnight, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::FalseKnight, eLayerType::Platform, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(1525.0f);
		Camera::SetMaxX(1825.0f);
		Camera::SetMinY(850.0f);
		Camera::SetMaxY(850.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1200.0f, 1300.0f - 149.0f));
		mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Wait);
		mFalseKnight->GetComponent<Transform>()->SetPos(Vector2(2100.0f, 1300.0f - 148.0f));

		//falseBossTheme->Play(true);
	}

	void FalseKnightBossScene::Exit()
	{
		Scene::Exit();
		falseBossTheme->Stop(true);
		mPlayer->SetState(GameObject::eState::Active);
		mTime = 0.0f;
		mFalseKnight->Reset();
		mFalseManager->Reset();

		startFlag = false;
		flag = false;
		flag2 = false;
	}
}