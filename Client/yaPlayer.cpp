#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"

namespace ya
{
	Player::Player()
	{

	}

	Player::~Player()
	{

	}

	void Player::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Cuphead", L"..\\Resources\\Idle.bmp");

		GameObject::Initialize();
	}

	void Player::Update()
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

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, mPos.x, mPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);

	}

	void Player::Release()
	{
		GameObject::Release();

	}
}
