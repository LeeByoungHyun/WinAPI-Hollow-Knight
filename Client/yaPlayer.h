#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class Animator;
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			Idle,
			Walk,
			Slash,
			SlashAlt,
		};

		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void idle();
		void walk();
		void slash();
		void slashAlt();

	private:
		ePlayerState mState;
		Animator* mAnimator;
		int direction = 1;	// 0 = left, 1 = right
	};
}



