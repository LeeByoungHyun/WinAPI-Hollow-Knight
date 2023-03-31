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

		// 싱글톤
		// 이미 인스턴스가 존재하면 인스턴스를 반환, 없다면 인스턴스 생성
		static FalseKnight* GetInstance()
		{
			if (instance == nullptr)
				instance = new FalseKnight();

			return instance;
		}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetFalseKnightState(eFalseKnightState state) { mState = state; }
		eFalseKnightState GetFalseKnightState() { return mState; }

		bool GetJumpReadyFlag() { return jumpReadyFlag; }

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

		void jumpAnticipateComplateEvent();
		void jumpComplateEvent();
		void landComplateEvent();
		void jumpAttackPart1ComplateEvent();
		void jumpAttackPart2ComplateEvent();
		void jumpAttackPart3ComplateEvent();

	private:
		class Animator* mAnimator;
		class Collider* mCollider;
		class Transform* tr;
		class RigidBody* mRigidbody;
		eFalseKnightState mState;
		eDirection mDirection;
		float mTime = 0.0f;
		int pattern;

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

		bool jumpReadyFlag = false;

		// 싱글톤 객체 인스턴스
		static FalseKnight* instance;
	};
}
