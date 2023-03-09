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

        // �� �Ŵ����� �� �߰�

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
        // ������� ����� �� ����
        mActiveScene->Exit();
        CollisionManager::Clear();

        // ���ο� ���� ����� �� ����
        mActiveScene = mScenes[(UINT)type];
        mActiveScene->Enter();
    }
}