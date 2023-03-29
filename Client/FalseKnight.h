#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FalseKnight : public GameObject
	{
	public:
		enum class eFalseKnightState
		{
			Idle,
			RunAnticipate,
			Run,
			JumpAnticipate,
			Jump,
			Land,
			AttackAnticipate,
			Attack,
			AttackRecover,
			JumpAttackUp,
			JumpAttackPart1,
			JumpAttackPart2,
			JumpAttackPart3,
			StunRoll,
			StunRollEnd,
			StunOpen,
			StunOpened,
			StunHit,
			Death,
		};

		enum class eDirection
		{
			Left,
			Right
		};

		FalseKnight();
		~FalseKnight();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();
		void runAnticipate();
		void run();
		void jumpAnticipate();
		void jump();
		void land();
		void attackAnticipate();
		void attack();
		void attackRecover();
		void jumpAttackUp();
		void jumpAttackPart1();
		void jumpAttackPart2();
		void jumpAttackPart3();
		void stunRoll();
		void stunRollEnd();
		void stunOpen();
		void stunOpened();
		void stunHit();
		void death();

	private:
		class Animator* mAnimator;
		class Collider* mCollider;
		class Transform* tr;
		class RigidBody* mRigidbody;
		eFalseKnightState mState;
		eDirection mDirection;

		bool idleFlag = false;
		bool runAnticipateFlag = false;
		bool runFlag = false;
		bool jumpAnticipateFlag = false;
		bool jumpFlag = false;
		bool landFlag = false;
		bool attackAnticipateFlag = false;
		bool attackFlag = false;
		bool attackRecoverFlag = false;
		bool jumpAttackUpFlag = false;
		bool jumpAttackPart1Flag = false;
		bool jumpAttackPart2Flag = false;
		bool jumpAttackPart3Flag = false;
		bool stunRollFlag = false;
		bool stunRollEndFlag = false;
		bool stunOpenFlag = false;
		bool stunOpenedFlag = false;
		bool stunHitFlag = false;
		bool deathFlag = false;
	};
}
