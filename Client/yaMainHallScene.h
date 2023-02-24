#pragma once
#include "yaScene.h"

#include "yaPlayer.h"
#include "yaBackboard.h"

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

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		Player* mPlayer;
		Backboard* mBackboard;
	};
}


