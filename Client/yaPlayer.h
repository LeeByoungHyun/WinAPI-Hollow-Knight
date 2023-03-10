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
			UpSlash
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

	private:
		void idle();
		void walk();
		void slash();
		void slashAlt();
		void upSlash();
		void dash();
		void jump();
		void fall();

		void SlashEndEvent();
		void SlashAltEndEvent();
		void UpSlashEndEvent();

		void DashEndEvent();

	private:
		ePlayerState mState;
		Transform* tr;
		Animator* mAnimator;
		Scene* curScene;
		eDirection mDirection = eDirection::Right;
	};
}



