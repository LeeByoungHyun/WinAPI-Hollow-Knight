#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MantisLordsManager : public GameObject
	{
	public:
		enum class ePhaseState
		{
			Phase1Start,
			Phase1,
			Phase2Start,
			Phase2,
			Phase2Combo1,
			Phase2Combo2,
			Phase2Combo3,
			Phase2Combo4,
			Phase2Combo5,
			Phase2Combo6,
			Phase3,
			End
		};

		MantisLordsManager();
		~MantisLordsManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Release() override;


	private:
		void phase1Start();
		void phase1();
		void phase2Start();
		void phase2();
		void phase3();

		void phase2Combo1();
		void phase2Combo2();
		void phase2Combo3();
		void phase2Combo4();
		void phase2Combo5();
		void phase2Combo6();

	private:
		class MantisLord1* mantisLord1;
		class MantisLord2* mantisLord2;
		class MantisLord3* mantisLord3;
		class MantisLordsProjectile* projectile1;
		class MantisLordsProjectile* projectile2;
		class MantisLordsProjectile* projectile3;

		ePhaseState mPhase;
		class Scene* activeScene;
		float mTime = 0.0f;

		bool StartFlag1 = false;
		bool StartFlag2 = false;
		bool startFlag3 = false;
		bool flag4 = false;

		bool mantis2AttackFlag = false;
		bool mantis3AttackFlag = false;

		bool mantis2DeathFlag = false;
		bool mantis3DeathFlag = false;
	};
}


