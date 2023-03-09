#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class SlashEffectRight : public GameObject
	{
	public:
		SlashEffectRight();
		~SlashEffectRight();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void slashEffectRightComplateEvent();

	private:
		Animator* mAnimator;
	};
}

