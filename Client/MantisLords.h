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

	private:
		eMantisLordsState mState;
		Transform* tr;
		Animator* mAnimator;
		Scene* curScene;
		eDirection mDirection = eDirection::Right;

		int hp;
	};
}

