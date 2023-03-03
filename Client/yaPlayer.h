#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
#include "yaTransform.h"
#include "yaAnimator.h"

namespace ya
{
	// class Animator;
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			Idle,
			Dash,
			Airborne,
			Slash,
			SlashAlt,
			UpSlash,
			DownSlash,
			Walk,
			Run,
			Fall,
			DoubleJump,
			Land,
			Recoil,
			Enter,
			Sit,
			GetOff,
			Turn,
			RunToIdle,
			Focus,
			FocusGet,
			FocusEnd,
			WallSlide,
			WallJump,
			Fireball1Cast,
			FireballAntic,
			Death,
			RespawnWake
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
		Image* mImage;
		Transform* tr;
		Animator* mAnimator;
	};
}



