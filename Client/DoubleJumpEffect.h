#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class DoubleJumpEffect : public GameObject
	{
	public:
		DoubleJumpEffect();
		~DoubleJumpEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void doubleJumpEffectComplateEvent();

	private:
		Animator* mAnimator;
		class Transform* tr;
		class Player* player;

		bool endFlag = false;
	};
}
