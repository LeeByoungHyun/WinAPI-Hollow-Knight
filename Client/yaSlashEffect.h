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

	private:
		Animator* mAnimator;
	};
}

