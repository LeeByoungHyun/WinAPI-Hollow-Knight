#pragma once
class SlashAltEffect
{
};

#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class SlashAltEffect : public GameObject
	{
	public:
		SlashAltEffect();
		~SlashAltEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		void slashAltEffectComplateEvent();

	private:
		Animator* mAnimator;
		GameObject* CollisionObj;
		class Player* player;
		class Transform* tr;
	};
}

