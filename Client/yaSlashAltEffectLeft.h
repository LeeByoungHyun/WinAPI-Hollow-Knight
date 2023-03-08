#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class SlashAltEffectLeft : public GameObject
	{
	public:
		SlashAltEffectLeft();
		~SlashAltEffectLeft();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}

