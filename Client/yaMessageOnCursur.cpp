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

		// 직접 팬을 만들어서 DC에 등록
		HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HBRUSH hBlueBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);    // 기본 팬 id값을 받아두고 새로운 팬 적용
		HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

		// 변경된 팬, 브러쉬로 사각형 그리기
		Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);

		// 기본 팬, 브러쉬로 변경
		SelectObject(hdc, hDefaultPen);
		SelectObject(hdc, hDefaultBrush);

		// 사용한 팬, 브러쉬 삭제 요청
		DeleteObject(hRedPen);
		DeleteObject(hBlueBrush);
	}

	void MessageOnCursur::Release()
	{
		GameObject::Release();

	}

}

