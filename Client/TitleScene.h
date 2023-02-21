#pragma once
#include "yaScene.h"

namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Release();


	};
}


