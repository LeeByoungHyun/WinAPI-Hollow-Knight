#pragma once
#include "yaScene.h"

namespace ya
{
	class MantisLordsBossScene : public Scene
	{
	public:
		MantisLordsBossScene();
		~MantisLordsBossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class Player* mPlayer;
		class MantisLord1* mantisLord1;
		class MantisLord2* mantisLord2;
		class MantisLord3* mantisLord3;
		class Sound* mantisLordsTheme;

		bool enterFlag = false;
		float mTime = 0.0f;
	};
}


