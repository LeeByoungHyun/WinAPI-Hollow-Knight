#include "yaLayer.h"

namespace ya
{
	Layer::Layer()
	{

	}

	Layer::~Layer()
	{

	}

	void Layer::Initialize()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;

			gameObject->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;

			gameObject->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;

			gameObject->Render(hdc);
		}
	}

	void Layer::Release()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			if (gameObject == nullptr)
				continue;

			gameObject->Release();
		}
	}

	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;

		mGameObjects.push_back(gameObj);
	}
}
