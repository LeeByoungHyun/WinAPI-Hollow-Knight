#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Block_Large : public GameObject
	{
	public:

		Block_Large();
		~Block_Large();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Image* mImage;
		class Transform* tr;
		class Collider* mCollider;
	};
}


