#include "yaMainHallScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"


namespace ya
{
	MainHallScene::MainHallScene()
	{

	}

	MainHallScene::~MainHallScene()
	{

	}

	void MainHallScene::Initialize()
	{
		// ���ӿ�����Ʈ �߰��� �̰���
		mPlayer = new Player();
		AddGameObject(mPlayer, eLayerType::Player);
		mPlayer->SetName(L"Player");

		// mPlayer->SetPos({ 800.0f, 800.0f });

		mBackboard = new Backboard();
		AddGameObject(mBackboard, eLayerType::BG);
		mBackboard->SetName(L"backboard");

		Scene::Initialize();
	}

	void MainHallScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Boss);
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
	}

	void MainHallScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void MainHallScene::Release()
	{
		Scene::Release();

	}

	void MainHallScene::Enter()
	{
		Scene::Enter();
	}

	void MainHallScene::Exit()
	{
		Scene::Exit();
	}
}