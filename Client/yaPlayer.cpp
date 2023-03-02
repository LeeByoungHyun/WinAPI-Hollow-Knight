#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"

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
		mImage = ResourceManager::Load<Image>(L"Player", L"..\\Resources\\Knight\\001.Idle\\001-00-007.bmp");

		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
		}

		tr->SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		// BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);

	}

	void Player::Release()
	{
		GameObject::Release();

	}

	/*
	void Player::SetPos(Vector2 pos)
	{
		tr = GetComponent<Transform>();
		tr->SetPos(pos);
	}
	*/
	
}