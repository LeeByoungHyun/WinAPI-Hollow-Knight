#pragma once
#include "yaGameObject.h"

namespace ya
{
	class HitCrackEffect : public GameObject
	{
	public:
		HitCrackEffect();
		~HitCrackEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void hitCrackEffectComplateEvent();

	private:
		class Animator* mAnimator;
		class Transform* tr;

		bool playFlag = false;
	};
}
