#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaObject.h"

namespace ya
{
	TitleScene::TitleScene()
	{

	}

	TitleScene::~TitleScene()
	{

	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
		Scene* scene = SceneManager::GetActiveScene();

		/*
		mMenuBG = new MenuBG();
		AddGameObject(mMenuBG, eLayerType::BG);
		mMenuBG->SetName(L"MenuBG");

		mMenuTitle = new MenuTitle();
		AddGameObject(mMenuTitle, eLayerType::BG);
		mMenuTitle->SetName(L"MenuTitle");

		mCursor = new Cursor();
		AddGameObject(mCursor, eLayerType::UI);
		mCursor->SetName(L"cursor");
		*/

		object::Instantiate<MenuBG>(eLayerType::BG);
		object::Instantiate<MenuTitle>(eLayerType::BG);
		object::Instantiate<Cursor>(eLayerType::UI);
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::MainHall);
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void TitleScene::Release()
	{
		Scene::Release();
	}

	void TitleScene::Enter()
	{

	}

	void TitleScene::Exit()
	{

	}
}