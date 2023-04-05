#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MantisLord2 : public GameObject
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
			DeathLeave,
			Gesture1,
			Gesture2,
		};

		enum class eDirection
		{
			Left,
			Right
		};

		MantisLord2();
		~MantisLord2();

		// 싱글톤
		// 이미 인스턴스가 존재하면 인스턴스를 반환, 없다면 인스턴스 생성
		static MantisLord2* GetInstance()
		{
			if (instance == nullptr)
				instance = new MantisLord2();

			return instance;
		}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eMantisLordsState GetState() { return mState; }
		void SetState(eMantisLordsState state) { mState = state; }
		void SetDirection(eDirection direction) { mDirection = direction; }
		eDirection GetDirection() { return mDirection; }

	private:
		void idle();
		void throneIdle();
		void throneBow();
		void throneStand();
		void throneLeave();
		void throneWounded();
		void gesture1();
		void gesture2();
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
		class Transform* tr;
		class Animator* mAnimator;
		class Collider* mCollider;
		class Scene* curScene;
		class Player* player;

		int hp;
		eDirection mDirection;
		double mTime = 0.0f;

		bool throneStandFlag = false;
		bool throneBowFlag = false;
		bool throneLeaveFlag = false;
		bool throneWoundedFlag = false;
		bool dashArriveFlag = false;
		bool dashAnticipateFlag = false;
		bool dashFlag = false;
		bool dashRecoverFlag = false;
		bool dashLeaveFlag = false;
		bool dStabArriveFlag = false;
		bool dStabFlag = false;
		bool dStabLandFlag = false;
		bool dStabLeaveFlag = false;
		bool wallArriveFlag = false;
		bool wallReadyFlag = false;
		bool throwFlag = false;
		bool wallLeave1Flag = false;
		bool wallLeave2Flag = false;
		bool gesture1Flag = false;
		bool gesture2Flag = false;
		bool deathFlag = false;
		bool deathLeaveFlag = false;

		class Sound* landGroundSound;
		class Sound* jumpOfGroundSound;
		class Sound* dashSound;
		class Sound* landWallSound;
		class Sound* jumpOfWallSound;
		class Sound* downSlashSound;
		class Sound* downSlashImpactSound;
		class Sound* downSlashArriveSound;
		class Sound* wallSlashSound;
		class Sound* deathSound;
		class Sound* damagedSound;

		// 싱글톤 객체 인스턴스
		static MantisLord2* instance;
	};
}

