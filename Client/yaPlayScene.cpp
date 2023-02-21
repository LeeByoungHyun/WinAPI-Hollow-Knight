#include "yaPlayScene.h"
#include "yaCuphead.h"
#include "yaMessageOnCursur.h"

namespace ya
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		Cuphead* cuphead = new Cuphead();
		AddGameObject(cuphead, eLayerType::Player);

		MessageOnCursur* mouse = new MessageOnCursur();
		AddGameObject(mouse, eLayerType::Player);

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();

	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void PlayScene::Release()
	{
		Scene::Release();

	}
}