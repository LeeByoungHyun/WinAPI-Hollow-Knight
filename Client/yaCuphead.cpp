#include "yaCuphead.h"
#include "yaTime.h"
#include "yaInput.h"

namespace ya
{
	Cuphead::Cuphead()
	{

	}

	Cuphead::~Cuphead()
	{

	}

	void Cuphead::Initialize()
	{
		GameObject::Initialize();
	}

	void Cuphead::Update()
	{
		GameObject::Update();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			mPos.x -= 100.0f * Time::DeltaTime();

		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			mPos.x += 100.0f * Time::DeltaTime();

		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			mPos.y -= 100.0f * Time::DeltaTime();

		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			mPos.y += 100.0f * Time::DeltaTime();

		}
	}

	void Cuphead::Render(HDC hdc)
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

	void Cuphead::Release()
	{
		GameObject::Release();

	}
}