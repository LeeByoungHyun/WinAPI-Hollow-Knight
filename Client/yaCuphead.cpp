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

	void Cuphead::Release()
	{
		GameObject::Release();

	}
}