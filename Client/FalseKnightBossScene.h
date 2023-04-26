#pragma once
#include "yaScene.h"

namespace ya
{
	class FalseKnightBossScene : public Scene
	{
	public:
		FalseKnightBossScene();
		~FalseKnightBossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class Player* mPlayer;
		class FalseKnight* mFalseKnight;
		class FalseKnightManager* mFalseManager;
		class Sound* falseBossTheme;
		class Sound* victorySound;
		float mTime = 0.0f;

		class HPInterface* hpUI;
		class HPobject01* hp01;
		class HPobject02* hp02;
		class HPobject03* hp03;
		class HPobject04* hp04;
		class HPobject05* hp05;
		class SoulUI* soulUI;
		class Fade* fade;

		bool startFlag = false;
		bool flag = false;
		bool flag2 = false;
	};
}


