#pragma once
#include "yaScene.h"

namespace ya
{
	class Player;
	class Backboard;
	class Crawlid;
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
		// Player* mPlayer;
		// Crawlid* mCrawlid;
		// Backboard* mBackboard;
	};
}


