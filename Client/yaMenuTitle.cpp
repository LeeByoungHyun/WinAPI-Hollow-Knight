#include "yaMenuTitle.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"

namespace ya
{
	MenuTitle::MenuTitle()
	{

	}

	MenuTitle::~MenuTitle()
	{

	}

	void MenuTitle::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"menu_title", L"..\\Resources\\TitleScene\\title.bmp");

		GameObject::Initialize();
	}

	void MenuTitle::Update()
	{
		GameObject::Update();
	}

	void MenuTitle::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		TransparentBlt(hdc, 400, 100, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		// BitBlt(hdc, 500, 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void MenuTitle::Release()
	{
		GameObject::Release();

	}
}