#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class Transform;
	class Animator;
	class Scene;
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			Idle,
			Walk,
			Jump,
			Fall,
			Dash,
			Slash,
			SlashAlt,
			UpSlash,
			Recoil,
			Death
		};

		enum class eDirection
		{
			Left,
			Right
		};

		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		int GetAtk() { return atk; }

	private:
		void idle();
		void walk();
		void slash();
		void slashAlt();
		void upSlash();
		void dash();
		void jump();
		void fall();
		void castFireball();
		void recoil();
		void death();

		void SlashEndEvent();
		void SlashAltEndEvent();
		void UpSlashEndEvent();
		void RecoilEndEvent();

		void DashEndEvent();
		void DeathEndEvent();

	private:
		ePlayerState mState;
		Transform* tr;
		Animator* mAnimator;
		Scene* curScene;
		eDirection mDirection = eDirection::Right;

		int hp;
		int atk;
		double mTime = 0.0f;

		bool walkFlag			= false;
		bool slashFlag			= false;
		bool slashAltFlag		= false;
		bool upSlashFlag		= false;
		bool dashFlag			= false;
		bool deathFlag			= false;
		bool invincibilityFlag	= false;
	};
}



