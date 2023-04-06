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
		scene->AddGameObject(mHornet, eLayerType::Monster);
		mHornet->Initialize();
		mHornet->GetComponent<Transform>()->SetPos(Vector2(1724.0f, 670.0f + 80.0f));
		mHornet->SetType(eLayerType::Monster);

		object::Instantiate<GodBG>(Vector2(1724.0f, 1800.0f), eLayerType::BG);
		object::Instantiate<FalseKnightPlatform>(Vector2(1724.0f, 1300.0f), eLayerType::Ground);

	}

	void HornetBossScene::Update()
	{
		Scene::Update();
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);

		Camera::SetTarget(mPlayer);
		Camera::SetMinX(1725.0f);
		Camera::SetMaxX(1725.0f);
		Camera::SetMinY(850.0f);
		Camera::SetMaxY(850.0f);

		mPlayer->GameObject::GetComponent<Transform>()->SetPos(Vector2(1600.0f, 1300.0f));
		mHornet->GetComponent<Transform>()->SetPos(Vector2(2100.0f, 1100.0f));
	}

	void HornetBossScene::Exit()
	{
		Scene::Exit();
	}
}