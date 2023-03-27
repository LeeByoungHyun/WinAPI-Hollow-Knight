#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MantisLordsManager : public GameObject
	{
	public:
		MantisLordsManager();
		~MantisLordsManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Release() override;

	private:
		class MantisLord1* mantisLord1;
		class MantisLord2* mantisLord2;
		class MantisLord3* mantisLord3;

		class Scene* activeScene;
		float mTime = 0.0f;

		bool StartFlag1 = false;
		bool StartFlag2 = false;
		bool startFlag3 = false;
		bool flag4 = false;
	};
}


