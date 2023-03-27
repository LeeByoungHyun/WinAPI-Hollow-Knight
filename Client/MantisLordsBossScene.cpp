#include "MantisLordsBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"

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

		object::Instantiate<MantisLordsManager>(eLayerType::Manager);	// 패턴관리매니저

		object::Instantiate<MantisThroneBack>(Vector2(1474.0f, 800.0f), eLayerType::BGObject);
		object::Instantiate<MantisThroneBack>(Vector2(1724.0f, 670.0f), eLayerType::BGObject);
		object::Instantiate<MantisThroneBack>(Vector2(1974.0f, 800.0f), eLayerType::BGObject);
		object::Instantiate<MantisThrone>(Vector2(1474.0f, 1430.0f), eLayerType::BGObject);
		object::Instantiate<MantisThrone>(Vector2(1724.0f, 1300.0f), eLayerType::BGObject);
		object::Instantiate<MantisThrone>(Vector2(1974.0f, 1430.0f), eLayerType::BGObject);

		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<MantisBossPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Ground);
		object::Instantiate<MantisBossWallLeft>(Vector2(1724.0f - 791.0f, 1300.0f), eLayerType::Wall);
		object::Instantiate<MantisBossWallRight>(Vector2(1724.0f + 791.0f, 1300.0f), eLayerType::Wall);

		// 싱글톤을 이용하여 모든 씬에서 플레이어가 1개만 존재하도록 함
		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(1725.0f);
		Camera::SetMaxX(1725.0f);
		Camera::SetMinY(850.0f);
		Camera::SetMaxY(850.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1600.0f, 1300.0f));
	}

	void MantisLordsBossScene::Exit()
	{
		Scene::Exit();
	}
}