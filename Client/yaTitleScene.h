#pragma once
#include "yaScene.h"

#include "yaMenuBG.h"
#include "yaCursor.h"
#include "yaMenuTitle.h"


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
		MenuBG* mMenuBG;
		Cursor* mCursor;
		MenuTitle* mMenuTitle;
	};
}


