#include "yaSceneManager.h"
#include "yaCollisionManager.h"

#include "MantisLordsBossScene.h"
#include "yaTitleScene.h"
#include "yaMainHallScene.h"
#include "FalseKnightBossScene.h"
#include "HornetBossScene.h"
#include "TutorialScene.h"
#include "EndingScene.h"

namespace ya
{
    std::vector<Scene*> SceneManager::mScenes = { };
    Scene* SceneManager::mActiveScene = nullptr;

    void SceneManager::Initialize()
    {
        mScenes.resize((UINT)eSceneType::End);

        // 씬 매니저에 씬 추가
        mScenes[(UINT)eSceneType::Title] = new TitleScene();
        mScenes[(UINT)eSceneType::Title]->SetType(eSceneType::Title);
        mScenes[(UINT)eSceneType::MantisLordsBoss] = new MantisLordsBossScene();
        mScenes[(UINT)eSceneType::MantisLordsBoss]->SetType(eSceneType::MantisLordsBoss);
        mScenes[(UINT)eSceneType::MainHall] = new MainHallScene();
        mScenes[(UINT)eSceneType::MainHall]->SetType(eSceneType::MainHall);
        mScenes[(UINT)eSceneType::FalseKnightBoss] = new FalseKnightBossScene();
        mScenes[(UINT)eSceneType::FalseKnightBoss]->SetType(eSceneType::FalseKnightBoss);
        mScenes[(UINT)eSceneType::HornetBoss] = new HornetBossScene();
        mScenes[(UINT)eSceneType::HornetBoss]->SetType(eSceneType::HornetBoss);
        mScenes[(UINT)eSceneType::Tutorial] = new TutorialScene();
        mScenes[(UINT)eSceneType::Tutorial]->SetType(eSceneType::Tutorial);
        mScenes[(UINT)eSceneType::Ending] = new EndingScene();
        mScenes[(UINT)eSceneType::Ending]->SetType(eSceneType::Ending);

        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
                continue;

            scene->Initialize();
        }

        mActiveScene = mScenes[(UINT)eSceneType::Title];
    }

    void SceneManager::Update()
    {
        mActiveScene->Update();
    }

    void SceneManager::Render(HDC hdc)
    {
        mActiveScene->Render(hdc);
    }

    void SceneManager::Destroy()
    {
        mActiveScene->Destroy();
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