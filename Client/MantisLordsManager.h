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

	private:
		class MantisLord1* mantisLord1;
		class MantisLord2* mantisLord2;
		class MantisLord3* mantisLord3;

		ePhaseState mPhase;
		class Scene* activeScene;
		float mTime = 0.0f;

		bool StartFlag1 = false;
		bool StartFlag2 = false;
		bool startFlag3 = false;
		bool flag4 = false;
	};
}


