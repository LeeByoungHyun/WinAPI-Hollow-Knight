#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MantisLordsProjectile : public GameObject
	{
	public:
		MantisLordsProjectile();
		~MantisLordsProjectile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Animator* mAnimator;
		class Transform* tr;
		class Collider* mCollider;

		float mTime = 0.0f;
	};
}
