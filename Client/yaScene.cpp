#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::End);
	}

	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		SceneManager::SetActiveScene(this);

		/*
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
		*/
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}

	void Scene::Release()
	{
		for (Layer& layer : mLayers)
		{
			layer.Release();
		}
	}

	void Scene::Destroy()
	{
		std::vector<GameObject*> deleteGameObjects = {};
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*>& gameObjects
				= layer.GetGameObjects();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end(); )
			{
				if ((*iter)->GetState() == GameObject::eState::Death)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameObjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}

		for (GameObject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = nullptr;
		}
	}

	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}

	std::vector<GameObject*>& Scene::GetGameObjects(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObjects();
	}

	void Scene::Enter()
	{

	}

	void Scene::Exit()
	{

	}

}