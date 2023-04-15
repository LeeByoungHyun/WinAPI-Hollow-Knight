#pragma once
#include "yaScene.h"

namespace ya
{
	class HornetBossScene : public Scene
	{
	public:
		HornetBossScene();
		~HornetBossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class Player* mPlayer;
		class Hornet* mHornet;

		bool enterFlag = false;
		float mTime = 0.0f;

		class HPobject01* hp01;
		class HPobject02* hp02;
		class HPobject03* hp03;
		class HPobject04* hp04;
		class HPobject05* hp05;
	};
}

