#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"

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
		mBackBoard = new BackBoard();
		AddGameObject(mBackBoard, eLayerType::BG);
		mBackBoard->SetName(L"backBoard");

		mCursor = new Cursor();
		AddGameObject(mCursor, eLayerType::UI);
		mCursor->SetName(L"cursor");

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void TitleScene::Release()
	{

	}
}