#include "yaSceneManager.h"
#include "yaBossScene.h"
#include "yaTitleScene.h"
#include "yaMainHallScene.h"
#include "yaCollisionManager.h"

namespace ya
{
    std::vector<Scene*> SceneManager::mScenes = { };
    Scene* SceneManager::mActiveScene = nullptr;

    void SceneManager::Initialize()
    {
        mScenes.resize((UINT)eSceneType::End);

        // 씬 매니저에 씬 추가

        mScenes[(UINT)eSceneType::Title] = new TitleScene();
        mScenes[(UINT)eSceneType::Title]->SetName(L"TitleScene");

        mScenes[(UINT)eSceneType::Boss] = new BossScene();
        mScenes[(UINT)eSceneType::Boss]->SetName(L"BossScene");

        mScenes[(UINT)eSceneType::MainHall] = new MainHallScene();
        mScenes[(UINT)eSceneType::MainHall]->SetName(L"MainHallScene");

        mActiveScene = mScenes[(UINT)eSceneType::Title];

        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
                continue;

            scene->Initialize();
        }
    }

    void SceneManager::Update()
    {
        mActiveScene->Update();
    }

    void SceneManager::Render(HDC hdc)
    {
        mActiveScene->Render(hdc);
    }

    void SceneManager::Release()
    {
        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
                continue;

            scene->Release();
        }
    }

    void SceneManager::LoadScene(eSceneType type)
    {
        // 현재씬이 종료될 때 실행
        mActiveScene->Exit();
        CollisionManager::Clear();

        // 새로운 씬이 실행될 때 실행
        mActiveScene = mScenes[(UINT)type];
        mActiveScene->Enter();
    }
}