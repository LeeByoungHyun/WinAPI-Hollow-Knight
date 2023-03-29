#include "FalseKnightBossScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"

#include "yaPlayer.h"
#include "FalseKnight.h"
#include "GodBG.h"
#include "FalseKnightPlatform.h"

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

		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<FalseKnightPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Ground);

		mFalseKnight = ya::FalseKnight::GetInstance();
		scene->AddGameObject(mFalseKnight, eLayerType::Monster);
		mFalseKnight->Initialize();
		mFalseKnight->GetComponent<Transform>()->SetPos(Vector2(1724.0f, 1000.0f));
		mFalseKnight->SetType(eLayerType::Monster);

		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);
	}

	void FalseKnightBossScene::Update()
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

		CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(1525.0f);
		Camera::SetMaxX(1825.0f);
		Camera::SetMinY(850.0f);
		Camera::SetMaxY(850.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1600.0f, 1300.0f));
	}

	void FalseKnightBossScene::Exit()
	{
		Scene::Exit();
	}
}