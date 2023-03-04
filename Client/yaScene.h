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

		void AddGameObject(GameObject* obj, eLayerType layer);
		const std::vector<GameObject*>& GetGameObjects(eLayerType layer);


		virtual void Enter();
		virtual void Exit();

	private:
		std::vector<Layer> mLayers;
	};
}


