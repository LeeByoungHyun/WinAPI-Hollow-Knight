#pragma once
#include "yaEntity.h"
#include "yaComponent.h"

namespace ya
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mcomponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mcomponents)
			{
				// RTTI
				if (dynamic_cast<T*>(comp))
				{
					return dynamic_cast<T*>(comp);
				}
			}

			return nullptr;
		}

	private:
		std::vector<Component*> mcomponents;
	};
}



