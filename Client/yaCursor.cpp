#include "yaCursor.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include <windowsx.h>

namespace ya
{
	Cursor::Cursor()
	{

	}

	Cursor::~Cursor()
	{

	}

	void Cursor::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Cursor", L"..\\Resources\\TitleScene\\Cursor.bmp");

		GameObject::Initialize();
	}

	void Cursor::Update()
	{
		GameObject::Update();

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		POINT mouse;
		::GetCursorPos(&mouse);

		pos.x = mouse.x - 105;
		pos.y = mouse.y - 100;

		tr->SetPos(pos);
	}

	void Cursor::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void Cursor::Release()
	{
		GameObject::Release();

	}
}