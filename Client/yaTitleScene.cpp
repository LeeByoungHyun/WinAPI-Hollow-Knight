#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaObject.h"
#include "yaSound.h"
#include "yaResourceManager.h"
#include "Fade.h"
#include "MenuGameStart.h"
#include "yaCollisionManager.h"

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
		object::Instantiate<Cursor>(eLayerType::Object);
		object::Instantiate<MenuGameStart>(eLayerType::BGObject);
		fade = ya::Fade::GetInstance();
		scene->AddGameObject(fade, eLayerType::Fade);
		fade->Initialize();
		fade->SetType(eLayerType::Fade);

		titletheme = ResourceManager::Load<Sound>(L"titletheme", L"..\\Resources\\Sound\\Title.wav");
		titletheme->Play(true);

		CollisionManager::SetLayer(eLayerType::Object, eLayerType::BGObject, true);
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::BG, true);
	}

	void TitleScene::Update()
	{
		Scene::Update();

		/*
		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Tutorial);
		}
		*/

		if (enterFlag == false)
		{
			fade->SetFadeColor(Fade::eColor::Black);
			fade->SetAlpha(255);
			fade->SetFadeState(Fade::eFadeState::FadeIn);
			enterFlag = true;
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
		titletheme->Play(true);

		CollisionManager::SetLayer(eLayerType::Object, eLayerType::BGObject, true);
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::BG, true);
	}

	void TitleScene::Exit()
	{
		titletheme->Stop(true);
		enterFlag = false;
	}
}