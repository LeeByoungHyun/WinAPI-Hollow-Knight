#pragma once
#include "yaScene.h"

namespace ya
{
	class MainHallScene : public Scene
	{
	public:
		MainHallScene();
		~MainHallScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		virtual void Destroy() override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class Player* mPlayer;
		class LongPlatform* platform1;
		class LongPlatform* platform2;
		class Fade* fade;
		class HPInterface* hpUI;
		class HPobject01* hp01;
		class HPobject02* hp02;
		class HPobject03* hp03;
		class HPobject04* hp04;
		class HPobject05* hp05;

		double mTime = 0.0f;
	};
}


