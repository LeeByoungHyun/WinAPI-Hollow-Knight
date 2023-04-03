#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FalseBarrel : public GameObject
	{
	public:
		FalseBarrel();
		~FalseBarrel();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		class Transform* tr;
		class Animator* mAnimator;
		class Collider* mCollider;
	};
}