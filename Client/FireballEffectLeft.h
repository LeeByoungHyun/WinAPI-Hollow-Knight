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

	private:
		void fireballEffectLeftEndEvent();

	private:
		Animator* mAnimator;
	};
}
