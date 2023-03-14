#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class SlashEffectLeft : public GameObject
	{
	public:
		SlashEffectLeft();
		~SlashEffectLeft();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		void slashEffectLeftComplateEvent();

	private:
		Animator* mAnimator;

		GameObject* CollisionObj;
	};
}

