#pragma once
#include "yaScene.h"
#include "yaBackBoard.h"

namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		BackBoard* mBackBoard;
	};
}


