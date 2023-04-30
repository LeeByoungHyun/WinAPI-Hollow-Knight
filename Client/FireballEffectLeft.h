#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class FireballEffectLeft : public GameObject
	{
	public:
		FireballEffectLeft();
		~FireballEffectLeft();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		void fireballEffectLeftEndEvent();

	private:
		Animator* mAnimator;
		class Transform* tr;
		bool hitFlag = false;
	};
}
