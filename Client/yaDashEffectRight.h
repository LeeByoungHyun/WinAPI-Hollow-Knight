#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class DashEffectRight : public GameObject
	{
	public:
		DashEffectRight();
		~DashEffectRight();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void dashEffectRightComplateEvent();

	private:
		Animator* mAnimator;
	};
}
