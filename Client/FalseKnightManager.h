#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FalseKnightManager : public GameObject
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

		FalseKnightManager();
		~FalseKnightManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Release() override;

	private:
		void phase1Start();
		void phase1();
		void phase2Start();
		void phase2();
		void phase3();

	private:
		class FalseKnight* mFalseKnight;

		ePhaseState mPhase;
		class Scene* activeScene;
		float mTime = 0.0f;
	};
}


