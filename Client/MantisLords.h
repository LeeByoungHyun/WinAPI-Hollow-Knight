#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class Transform;
	class Animator;
	class Scene;
	class MantisLords : public GameObject
	{
	public:
		enum class eMantisLordsState
		{
			Idle,
			ThroneIdle,
			ThroneBow,
			ThroneStand,
			ThroneLeave,
			ThroneWounded,
			DashArrive,
			DashAnticipate,
			Dash,
			DashRecover,
			DashLeave,
			DstabArrive,
			Dstab,
			DstabLand,
			DstabLeave,
			WallArrive,
			WallReady,
			Throw,
			WallLeave1,
			WallLeave2,
			Death,
			DeathLeave
		};

		enum class eDirection
		{
			Left,
			Right
		};

		MantisLords();
		~MantisLords();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();
		void throneIdle();
		void throneBow();
		void throneStand();
		void throneLeave();
		void throneWounded();
		void dashArrive();
		void dashAnticipate();
		void dash();
		void dashRecover();
		void dashLeave();
		void wallArrive();
		void wallReady();
		void wallThrow();
		void wallLeave1();
		void wallLeave2();
		void death();
		void deathLeave();	
		void dStabArrive();
		void dStab();
		void dStabLand();
		void dStabLeave();

	private:
		eMantisLordsState mState;
		Transform* tr;
		Animator* mAnimator;
		Scene* curScene;

		int hp;
		eDirection mDirection;
		double mTime = 0.0f;
		
		bool throneStandFlag	= false;
		bool throneBowFlag		= false;
		bool throneLeaveFlag	= false;
		bool throneWoundedFlag	= false;
		bool dashArriveFlag		= false;
		bool dashAnticipateFlag = false;
		bool dashFlag			= false;
		bool dashRecoverFlag	= false;
		bool dashLeaveFlag		= false;
		bool dStabArriveFlag	= false;
		bool dStabFlag			= false;
		bool dStabLandFlag		= false;
		bool dStabLeaveFlag		= false;
		bool wallArriveFlag		= false;
		bool wallReadyFlag		= false;
		bool throwFlag			= false;
		bool wallLeave1Flag		= false;
		bool wallLeave2Flag		= false;
	};
}

