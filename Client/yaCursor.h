#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Cursor : public GameObject
	{
	public:

		Cursor();
		~Cursor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
		class Collider* mCollider;
	};
}

