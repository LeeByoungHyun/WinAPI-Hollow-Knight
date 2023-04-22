#pragma once
#include "yaGameObject.h"

namespace ya
{
	class StunEffect : public GameObject
	{
	public:
		StunEffect();
		~StunEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void StunEffectComplateEvent();

	private:
		class Animator* mAnimator;
		class Transform* tr;

		bool playFlag = false;
	};
}
