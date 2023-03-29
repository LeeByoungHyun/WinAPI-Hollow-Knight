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
	};
}


