#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FireballHitEffect : public GameObject
	{
	public:
		FireballHitEffect();
		~FireballHitEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void FireballHitEffectComplateEvent();

	private:
		class Animator* mAnimator;
		class Transform* tr;

		bool playFlag = false;
	};
}
