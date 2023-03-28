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
		class Animator* mAnimator;
		class Collider* mCollider;
		class Transform* tr;

	};
}
