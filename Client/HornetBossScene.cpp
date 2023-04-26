#include "HornetBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaResourceManager.h"
#include "yaSound.h"
#include "yaTime.h"

#include "Hornet.h"
#include "yaPlayer.h"
#include "GodBG.h"
#include "FalseKnightPlatform.h"
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

namespace ya
{
	HornetBossScene::HornetBossScene()
	{

	}

	HornetBossScene::~HornetBossScene()
	{

	}

	void HornetBossScene::Initialize()
	{
		Scene::Initialize();

		Scene* scene = SceneManager::GetActiveScene();

		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);

		mHornet = ya::Hornet::GetInstance();
		scene->AddGameObject(mHornet, eLayerType::Hornet);
		mHornet->Initialize();
		mHornet->GetComponent<Transform>()->SetPos(Vector2(1724.0f, 670.0f + 80.0f));
		mHornet->SetType(eLayerType::Hornet);

		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<FalseKnightPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Platform);

		object::Instantiate<HornetWallLeft>(Vector2(1724.0f - 791.0f, 1300.0f), eLayerType::Wall);
		object::Instantiate<HornetWallRight>(Vector2(1724.0f + 791.0f, 1300.0f), eLayerType::Wall);

		victorySound = ResourceManager::Load<Sound>(L"VictorySound", L"..\\Resources\\Sound\\Hallownest_Call.wav");
		HornetBossSound = ResourceManager::Load<Sound>(L"HornetBossSound", L"..\\Resources\\Sound\\Hornet\\S45 HORNET-110.wav");

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

	void HornetBossScene::Update()
	{
		Scene::Update();

		if (Fade::GetInstance()->GetFadeState() == Fade::eFadeState::Neutral && startFlag == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 3.0f)
			{
				HornetBossSound->Play(true);
				mHornet->SetHornetState(Hornet::eHornetState::Idle);
				startFlag = true;
				mTime = 0.0f;
			}
		}

		if (mHornet->GetHornetState() == Hornet::eHornetState::Wounded)
		{
			mTime += Time::DeltaTime();
			HornetBossSound->Stop(true);
			if (mTime >= 5.0f && flag == false)
			{
				Fade::GetInstance()->SetFadeColor(Fade::eColor::White);
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeOut);
				victorySound->Play(false);
				flag = true;
			}
			if (mTime >= 9.0f)
			{
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeIn);
				SceneManager::LoadScene(eSceneType::MantisLordsBoss);
				mTime = 0.0f;
			}
		}
	}

	void HornetBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void HornetBossScene::Release()
	{
		Scene::Release();
	}

	void HornetBossScene::Enter()
	{
		Scene::Enter();

		CollisionManager::SetLayer(eLayerType::NeilEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::SpellEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::NeilEffect, eLayerType::Hornet, true);
		CollisionManager::SetLayer(eLayerType::SpellEffect, eLayerType::Hornet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Hornet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Platform, true);
		CollisionManager::SetLayer(eLayerType::Hornet, eLayerType::Platform, true);
		CollisionManager::SetLayer(eLayerType::Hornet, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Hornet, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(1725.0f);
		Camera::SetMaxX(1725.0f);
		Camera::SetMinY(850.0f);
		Camera::SetMaxY(850.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1600.0f, 1300.0f - 148.0f));
		mHornet->GetComponent<Transform>()->SetPos(Vector2(2100.0f, 1100.0f));

		//HornetBossSound->Play(true);
	}

	void HornetBossScene::Exit()
	{
		Scene::Exit();

		HornetBossSound->Stop(true);
		mHornet->Initialize();
		mTime = 0.0f;
		flag = false;
		startFlag = false;
	}
}