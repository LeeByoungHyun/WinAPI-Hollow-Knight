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
			ThrowNeedleAnticipate,
			ThrowNeedle,
			ThrowNeedleRecover,
			CounterAnticipate,
			CounterStance,
			CounterEnd,
			CounterAttackAnticipate,
			CounterAttack,
			CounterAttackRecover,	// 이하 스프라이트 없음
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

		// 싱글톤
		// 이미 인스턴스가 존재하면 인스턴스를 반환, 없다면 인스턴스 생성
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
		void jumpAnticipate();
		void jump();
		void land();
		void gDashAnticipate();
		void gDash();
		void gDashRecover();
		void aDashAnticipate();
		void aDash();
		void aDashRecover();
		void sphereAnticipateG();
		void sphereAnticipateA();
		void sphere();
		void sphereRecover();
		void throwNeedleAnticipate();
		void throwNeedle();
		void throwNeedleRecover();
		void counterAnticipate();
		void counterStance();
		void counterEnd();
		void counterAttackAnticipate();
		void counterAttack();
		void counterAttackRecover();
		void barbThrowAnticipate();
		void barbThrow();
		void barbThrowRecover();
		void stunAir();
		void stun();
		void wounded();
		void flash();

		void jumpAnticipateCompleteEvent();
		void jumpCompleteEvent();
		void landCompleteEvent();
		void sphereAnticipateACompleteEvent();
		void sphereAnticipateGCompleteEvent();
		void sphereCompleteEvent();
		void sphereRecoverCompleteEvent();
		void aDashAnticipateCompleteEvent();
		void aDashRecoverCompleteEvent();
		void aDashCompleteEvent();
		void gDashAnticipateCompleteEvent();
		void gDashRecoverCompleteEvent();
		void gDashCompleteEvent();
		void throwNeedleAnticipateCompleteEvent();
		void throwNeedleCompleteEvent();
		void throwNeedleRecoverCompleteEvent();
		void counterAnticipateCompleteEvent();
		void counterStanceCompleteEvent();
		void counterEndCompleteEvent();
		void counterAttackAnticipateCompleteEvent();
		void counterAttackCompleteEvent();
		void counterAttackRecoverCompleteEvent();

		void initializeFlag();

	private:
		class Transform*	tr;
		class Animator*		mAnimator;
		class Scene*		curScene;
		class RigidBody*	mRigidBody;
		class Collider*		mCollider;

		eHornetState mState;
		eDirection mDirection = eDirection::Left;
		int jumpPattern;
		int idlePattern;
		float mTime = 0.0f;
		int hp;
		int stunHp;

		bool idleFlag						= false;
		bool runFlag						= false;
		bool jumpAnticipateFlag				= false;
		bool jumpFlag						= false;
		bool landFlag						= false;
		bool gDashAnticipateFlag			= false;
		bool gDashFlag						= false;
		bool gDashRecoverFlag				= false;
		bool aDashAnticipateFlag			= false;
		bool aDashFlag						= false;
		bool aDashRecoverFlag				= false;
		bool sphereAnticipateGFlag			= false;
		bool sphereAnticipateAFlag			= false;
		bool sphereFlag						= false;
		bool sphereRecoverFlag				= false;
		bool throwNeedleAnticipateFlag		= false;
		bool throwNeedleFlag				= false;
		bool throwNeedleRecoverFlag			= false;
		bool counterAnticipateFlag			= false;
		bool counterStanceFlag				= false;
		bool counterEndFlag					= false;
		bool counterAttackAnticipateFlag	= false;
		bool counterAttackFlag				= false;
		bool counterAttackRecoverFlag		= false;
		bool barbThrowAnticipateFlag		= false;
		bool barbThrowFlag					= false;
		bool barbThrowRecoverFlag			= false;
		bool stunAirFlag					= false;
		bool stunFlag						= false;
		bool woundedFlag					= false;
		bool flashFlag						= false;
		bool eventFlag						= false;

		// 싱글톤 객체 인스턴스
		static Hornet* instance;
	};
}


