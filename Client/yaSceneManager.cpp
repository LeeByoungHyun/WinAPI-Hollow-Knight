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

        // �� �Ŵ����� �� �߰�
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
        // ������� ����� �� ����
        mActiveScene->Exit();

        // ���ο� ���� ����� �� ����
        mActiveScene = mScenes[(UINT)type];
        mActiveScene->Enter();
    }
}