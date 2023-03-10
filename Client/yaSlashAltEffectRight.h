#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class SlashAltEffectRight : public GameObject
	{
	public:
		SlashAltEffectRight();
		~SlashAltEffectRight();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void slashAltEffectRightComplateEvent();

	private:
		Animator* mAnimator;
	};
}

