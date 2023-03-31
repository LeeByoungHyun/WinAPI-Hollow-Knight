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
			End
		};

		FalseKnightManager();
		~FalseKnightManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Release() override;

	private:
		void phase1();
		void phase2();
		void pattern1();
		void pattern2();
		void pattern3();
		void pattern4();

	private:
		class FalseKnight* mFalseKnight;

		ePhaseState mPhase;
		class Scene* activeScene;
		float mTime = 0.0f;
		int pattern;

		bool count1 = false;
		bool pattern1Flag = false;
		bool pattern2Flag = false;
		bool pattern3Flag = false;
		bool pattern4Flag = false;

		bool flag2 = false;
		bool flag3 = false;
	};
}


