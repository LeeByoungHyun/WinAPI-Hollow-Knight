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

	};
}


