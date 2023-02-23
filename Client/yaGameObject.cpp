#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	GameObject::GameObject()
	{
		mcomponents.resize((UINT)eComponentType::End);
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Initialize()
	{
		for (Component* component : mcomponents)
		{
			if (component == nullptr)
				continue;

			component->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* component : mcomponents)
		{
			if (component == nullptr)
				continue;

			component->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* component : mcomponents)
		{
			if (component == nullptr)
				continue;

			component->Render(hdc);
		}
	}

	void GameObject::Release()
	{
		for (Component* component : mcomponents)
		{
			if (component == nullptr)
				continue;

			component->Release();
		}
	}
}