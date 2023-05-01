#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FalseKnightManager : public GameObject
	{
	public:
		enum class ePhaseState
		{
			Phase1,
			Phase2,
			Pattern1,
			Pattern2,
			Pattern3,
			Pattern4,
			Pattern5,
			Rage,
			Stun,
			RageAttack,
			End
		};

		FalseKnightManager();
		~FalseKnightManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Release() override;

		ePhaseState GetPhaseState() { return mPhase; }
		void Reset();

	private:
		void phase1();
		void phase2();
		void pattern1();
		void pattern2();
		void pattern3();
		void pattern4();
		void pattern5();
		void rage();
		void stun();
		void rageAttack();

	private:
		class FalseKnight* mFalseKnight;
		class StunHead* mHead;
		class Sound* victorySound;

		ePhaseState mPhase;
		class Scene* activeScene;
		float mTime = 0.0f;
		float endTime = 0.0f;
		int pattern;

		bool enterFlag = false;
		bool pattern1Flag = false;
		bool pattern2Flag = false;
		bool pattern3Flag = false;
		bool pattern4Flag = false;
		bool check1Flag = false;
		bool check2Flag = false;
		bool stunFlag = false;
		bool rageFlag = false;
		bool rageAttackFlag = false;
		int rageCount = 0;
		bool stuned = false;
		bool flag = false;
		bool flag2 = false;
	};
}


