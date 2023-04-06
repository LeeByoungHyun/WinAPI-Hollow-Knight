#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Hornet : public GameObject
	{
	public:
		enum class eHornetState
		{
			Idle,
			Run,
			JumpAnticipate,
			Jump,
			Land,
			GDashAnticipate,
			GDash,
			GDashRecover,
			ADashAnticipate,
			ADash,
			ADashRecover,
			SphereAnticipateG,
			SphereAnticipateA,
			Sphere,
			SphereRecover,
			ThrowAnticipate,
			Throw,
			ThrowRecover,
			CounterAnticipate,
			CounterStance,
			CounterEnd,
			CounterAttackAnticipate,
			CounterAttack,
			CounterAttackRecover,	// ���� ��������Ʈ ����
			BarbThrowAnticipate,
			BarbThrow,
			BarbThrowRecover,
			StunAir,
			Stun,
			Wounded,
			Flash
		};

		enum class eDirection
		{
			Left,
			Right
		};

		Hornet();
		~Hornet();

		// �̱���
		// �̹� �ν��Ͻ��� �����ϸ� �ν��Ͻ��� ��ȯ, ���ٸ� �ν��Ͻ� ����
		static Hornet* GetInstance()
		{
			if (instance == nullptr)
				instance = new Hornet();

			return instance;
		}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();
		void run();

	private:
		class Transform*	tr;
		class Animator*		mAnimator;
		class Scene*		curScene;
		class RigidBody*	mRigidBody;
		class Collider*		mCollider;

		eHornetState mState;
		eDirection mDirection = eDirection::Left;

		bool idleFlag = false;
		bool runFlag = false;

		// �̱��� ��ü �ν��Ͻ�
		static Hornet* instance;
	};
}


