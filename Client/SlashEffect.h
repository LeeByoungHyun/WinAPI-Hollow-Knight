#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class SlashEffect : public GameObject
	{
	public:
		SlashEffect();
		~SlashEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		void slashEffectComplateEvent();

	private:
		Animator* mAnimator;
		GameObject* CollisionObj;
		class Player* player;
		class Transform* tr;
	};
}

