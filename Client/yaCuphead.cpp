#include "yaCuphead.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"

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
		mImage = ResourceManager::Load<Image>(L"Cuphead", L"..\\Resources\\Idle.bmp");

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

		BitBlt(hdc, mPos.x, mPos.y, mImage->GetWidth(), mImage->GetHeight() , mImage->GetHdc(), 0, 0, SRCCOPY);

	}

	void Cuphead::Release()
	{
		GameObject::Release();

	}
}