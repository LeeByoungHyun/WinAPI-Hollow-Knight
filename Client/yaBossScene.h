#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaGrimRoomBG.h"

namespace ya
{
	class BossScene : public Scene
	{
	public:
		BossScene();
		~BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		Player* mPlayer;
		GrimRoomBG* mGrimRoomBG;
	};
}


