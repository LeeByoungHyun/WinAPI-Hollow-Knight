#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTitleScene.h"

namespace ya
{
    std::vector<Scene*> SceneManager::mScenes = { };
    Scene* SceneManager::mActiveScene = nullptr;

    void SceneManager::Initialize()
    {
        mScenes.resize((UINT)eSceneType::End);

        // 씬 매니저에 씬 추가
        mScenes[(UINT)eSceneType::Play] = new PlayScene();
        mScenes[(UINT)eSceneType::Play]->SetName(L"PlayScene");

        mScenes[(UINT)eSceneType::Title] = new TitleScene();
        mScenes[(UINT)eSceneType::Title]->SetName(L"TitleScene");

        mActiveScene = mScenes[(UINT)eSceneType::Play];

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

        // 새로운 씬이 실행될 때 실행
        mActiveScene = mScenes[(UINT)type];
        mActiveScene->Enter();
    }
}