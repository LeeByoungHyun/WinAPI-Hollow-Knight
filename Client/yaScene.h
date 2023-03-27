#pragma once
#include "yaEntity.h"
#include "yaLayer.h"

namespace ya
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		virtual void Destroy();

		void AddGameObject(GameObject* obj, eLayerType layer);
		std::vector<GameObject*>& GetGameObjects(eLayerType layer);

		eSceneType GetType() { return mType; }
		void SetType(eSceneType type) { mType = type; }

		virtual void Enter();
		virtual void Exit();

	private:
		std::vector<Layer> mLayers;

		eSceneType mType;
	};
}


