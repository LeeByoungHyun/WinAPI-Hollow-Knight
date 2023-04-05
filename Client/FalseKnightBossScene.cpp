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
		object::Instantiate<FalseKnightPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Ground);

		mFalseManager = object::Instantiate<FalseKnightManager>(eLayerType::Manager);
		mFalseKnight = ya::FalseKnight::GetInstance();
		scene->AddGameObject(mFalseKnight, eLayerType::Monster);
		mFalseKnight->Initialize();
		mFalseKnight->SetType(eLayerType::Monster);

		mPlayer = ya::Player::GetInstance();
		scene->AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->Initialize();
		mPlayer->SetType(eLayerType::Player);

		falseBossTheme = ResourceManager::Load<Sound>(L"falseKnightTheme", L"..\\Resources\\Sound\\False Knight\\Boss Battle 1.wav");
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

		CollisionManager::SetLayer(eLayerType::NeilEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::SpellEffect, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(1525.0f);
		Camera::SetMaxX(1825.0f);
		Camera::SetMinY(850.0f);
		Camera::SetMaxY(850.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1600.0f, 1300.0f));
		mFalseKnight->GetComponent<Transform>()->SetPos(Vector2(2100.0f, 1100.0f));

		falseBossTheme->Play(true);
	}

	void FalseKnightBossScene::Exit()
	{
		Scene::Exit();
		falseBossTheme->Stop(true);
	}
}