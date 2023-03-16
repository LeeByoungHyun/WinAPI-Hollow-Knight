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
	};
}


