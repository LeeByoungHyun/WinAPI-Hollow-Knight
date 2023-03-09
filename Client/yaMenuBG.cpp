#include "yaMenuBG.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"

namespace ya
{
	MenuBG::MenuBG()
	{

	}

	MenuBG::~MenuBG()
	{

	}

	void MenuBG::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"menu_BG", L"..\\Resources\\TitleScene\\Voidheart_menu_BG.bmp");

		GameObject::Initialize();
	}

	void MenuBG::Update()
	{
		GameObject::Update();
	}

	void MenuBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void MenuBG::Release()
	{
		GameObject::Release();

	}
}