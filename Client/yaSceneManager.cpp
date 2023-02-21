#include "yaSceneManager.h"
#include "yaPlayScene.h"

namespace ya
{
    std::vector<Scene*> SceneManager::mScenes = { };

    void SceneManager::Initialize()
    {
        mScenes.resize((UINT)eSceneType::Max);

        // ¾À ¸Å´ÏÀú¿¡ ¾À Ãß°¡
        mScenes[(UINT)eSceneType::Play] = new PlayScene();

        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
                continue;

            scene->Initialize();
        }
    }

    void SceneManager::Update()
    {
        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
                continue;

            scene->Update();
        }
    }

    void SceneManager::Render(HDC hdc)
    {
        for (Scene* scene : mScenes)
        {
            if (scene == nullptr)
                continue;

            scene->Render(hdc);
        }
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
}