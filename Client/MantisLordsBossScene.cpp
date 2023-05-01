#include "MantisLordsBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaResourceManager.h"
#include "yaSound.h"
#include "yaTime.h"

#include "yaPlayer.h"
#include "GodBG.h"
#include "MantisLord1.h"
#include "MantisLord2.h"
#include "MantisLord3.h"
#include "MantisLordsManager.h"
#include "yaCrawlid.h"
#include "GroundCollider.h"
#include "LongPlatform.h"
#include "MantisBossPlatform.h"
#include "MantisBossWallLeft.h"
#include "MantisBossWallRight.h"
#include "MantisThrone.h"
#include "MantisThroneBack.h"
#include "HPInterface.h"
#include "HPobject01.h"
#include "HPobject02.h"
#include "HPobject03.h"
#include "HPobject04.h"
#include "HPobject05.h"
#include "Spike.h"
#include "Fade.h"
#include "SoulUI.h"
#include "Mantis_Cage_L.h"
#include "Mantis_Cage_R.h"
#include "Mantis_Cage_T.h"
#include "Pillar_Large.h"
#include "Egg_01.h"
#include "Egg_02.h"
#include "Egg_03.h"

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

		mantisLord1 = ya::MantisLord1::GetInstance();
		scene->AddGameObject(mantisLord1, eLayerType::Monster);
		mantisLord1->Initialize();
		mantisLord1->GetComponent<Transform>()->SetPos(Vector2(1724.0f, 670.0f + 80.0f));
		mantisLord1->SetType(eLayerType::Monster);
		mantisLord2 = ya::MantisLord2::GetInstance();
		scene->AddGameObject(mantisLord2, eLayerType::Monster);
		mantisLord2->Initialize();
		mantisLord2->GetComponent<Transform>()->SetPos(Vector2(1474.0f, 800.0f + 80.0f));
		mantisLord2->SetType(eLayerType::Monster);
		mantisLord3 = ya::MantisLord3::GetInstance();
		scene->AddGameObject(mantisLord3, eLayerType::Monster);
		mantisLord3->Initialize();
		mantisLord3->GetComponent<Transform>()->SetPos(Vector2(1974.0f, 800.0f + 80.0f));
		mantisLord3->SetType(eLayerType::Monster);
		manager = object::Instantiate<MantisLordsManager>(eLayerType::Manager);	// 패턴관리매니저

		object::Instantiate<Pillar_Large>(Vector2(1724.0f - 500.0f, 1530.0f), eLayerType::BGObject);
		object::Instantiate<Pillar_Large>(Vector2(1724.0f + 500.0f, 1530.0f), eLayerType::BGObject);
		object::Instantiate<Mantis_Cage_L>(Vector2(1724.0f - 700.0f, 1330.0f), eLayerType::BGObject);
		object::Instantiate<Mantis_Cage_L>(Vector2(1724.0f - 550.0f, 1430.0f), eLayerType::BGObject);
		object::Instantiate<Mantis_Cage_L>(Vector2(1724.0f - 400.0f, 1530.0f), eLayerType::BGObject);
		object::Instantiate<Mantis_Cage_R>(Vector2(1724.0f + 700.0f, 1330.0f), eLayerType::BGObject);
		object::Instantiate<Mantis_Cage_R>(Vector2(1724.0f + 550.0f, 1430.0f), eLayerType::BGObject);
		object::Instantiate<Mantis_Cage_R>(Vector2(1724.0f + 400.0f, 1530.0f), eLayerType::BGObject);
		//object::Instantiate<Mantis_Cage_T>(Vector2(1724.0f, 700.0f), eLayerType::BGObject);
		object::Instantiate<MantisThroneBack>(Vector2(1474.0f, 800.0f), eLayerType::BGObject);
		object::Instantiate<MantisThroneBack>(Vector2(1724.0f, 670.0f), eLayerType::BGObject);
		object::Instantiate<MantisThroneBack>(Vector2(1974.0f, 800.0f), eLayerType::BGObject);
		object::Instantiate<MantisThrone>(Vector2(1474.0f, 1430.0f), eLayerType::BGObject);
		object::Instantiate<MantisThrone>(Vector2(1724.0f, 1300.0f), eLayerType::BGObject);
		object::Instantiate<MantisThrone>(Vector2(1974.0f, 1430.0f), eLayerType::BGObject);

		//object::Instantiate<Egg_02>(Vector2(1500.0f, 1300.0f), eLayerType::BGObject);
		//object::Instantiate<Egg_01>(Vector2(1400.0f, 1320.0f), eLayerType::BGObject);
		//object::Instantiate<Egg_03>(Vector2(1570.0f, 1310.0f), eLayerType::BGObject);



		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<MantisBossPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Platform);
		object::Instantiate<MantisBossWallLeft>(Vector2(1724.0f - 791.0f, 1300.0f), eLayerType::Wall);
		object::Instantiate<MantisBossWallRight>(Vector2(1724.0f + 791.0f, 1300.0f), eLayerType::Wall);
		object::Instantiate<Spike>(Vector2(1724.0f - 691.0f, 1300.0f), eLayerType::Spike);
		object::Instantiate<Spike>(Vector2(1724.0f + 691.0f, 1300.0f), eLayerType::Spike);
		object::Instantiate<Spike>(Vector2(1724.0f - 631.0f, 1300.0f), eLayerType::Spike);
		object::Instantiate<Spike>(Vector2(1724.0f + 631.0f, 1300.0f), eLayerType::Spike);


		// 싱글톤을 이용하여 모든 씬에서 플레이어가 1개만 존재하도록 함
		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);

		mantisLordsTheme = ResourceManager::Load<Sound>(L"MantisLordstheme", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_theme2.wav");
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

	void MantisLordsBossScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			//SceneManager::LoadScene(eSceneType::MainHall);
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			//SceneManager::LoadScene(eSceneType::Title);
		}

		if (Fade::GetInstance()->GetFadeState() == Fade::eFadeState::Neutral && startFlag == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 3.0f)
			{
				mantisLordsTheme->Play(true);
				manager->SetManagerState(MantisLordsManager::ePhaseState::Phase1Start);
				startFlag = true;
				mTime = 0.0f;
			}
		}

		if (manager->GetEndFlag() == true)
		{
			mTime += Time::DeltaTime();

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
				SceneManager::LoadScene(eSceneType::Ending);
				mTime = 0.0f;
			}
		}

		if (mantisLord1->GetState() == MantisLord1::eMantisLordsState::ThroneBow)
		{
			mantisLordsTheme->Stop(true);
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

		CollisionManager::SetLayer(eLayerType::NeilEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::SpellEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Platform, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Spike, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(1725.0f);
		Camera::SetMaxX(1725.0f);
		Camera::SetMinY(850.0f);
		Camera::SetMaxY(850.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1600.0f, 1300.0f - 99.0f));
		enterFlag = true;
	}

	void MantisLordsBossScene::Exit()
	{
		Scene::Exit();

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1724.0f, 1300.0f));
		mantisLordsTheme->Stop(true);
	}
}