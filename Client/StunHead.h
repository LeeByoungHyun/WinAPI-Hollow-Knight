#include "yaGameObject.h"

#pragma once
namespace ya
{
	class StunHead : public GameObject
	{
	public:
		enum class eStunHeadState
		{
			Idle,
			Hit,
			Death
		};

		enum class eDirection
		{
			Left,
			Right
		};

		StunHead();
		~StunHead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetHeadDirection(eDirection direct) { mDirection = direct; }

	private:
		void idle();
		void hit();
		void death();

		void hitCompleteEvent();
		void deathHead1CompleteEvent();

	private:
		class Animator* mAnimator;
		class Collider* mCollider;
		class Transform* tr;
		//class RigidBody* mRigidbody;
		eStunHeadState mState;
		eDirection mDirection;
		float mTime = 0.0f;
		class FalseKnight* mFalseKnight;
		class Player* mPlayer;
		bool idleFlag = false;
		bool hitFlag = false;
		bool deathFlag1 = false;
		bool deathFlag2 = false;
		bool deathFlag3 = false;
	};
}
