#include "yaMessageOnCursur.h"
#include "yaTime.h"
#include <windowsx.h>

namespace ya
{
	MessageOnCursur::MessageOnCursur()
	{

	}

	MessageOnCursur::~MessageOnCursur()
	{

	}

	void MessageOnCursur::Initialize()
	{
		GameObject::Initialize();

	}

	void MessageOnCursur::Update()
	{
		GameObject::Update();

		POINT mouse;
		::GetCursorPos(&mouse);

		mPos.x = mouse.x - 90;
		mPos.y = mouse.y - 130;
	}

	void MessageOnCursur::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// ���� ���� ���� DC�� ���
		HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HBRUSH hBlueBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);    // �⺻ �� id���� �޾Ƶΰ� ���ο� �� ����
		HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

		// ����� ��, �귯���� �簢�� �׸���
		Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);

		// �⺻ ��, �귯���� ����
		SelectObject(hdc, hDefaultPen);
		SelectObject(hdc, hDefaultBrush);

		// ����� ��, �귯�� ���� ��û
		DeleteObject(hRedPen);
		DeleteObject(hBlueBrush);
	}

	void MessageOnCursur::Release()
	{
		GameObject::Release();

	}

}

