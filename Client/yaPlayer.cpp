#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaSlashEffect.h"
#include "yaScene.h"

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
		// mImage = ResourceManager::Load<Image>(L"Player", L"..\\Resources\\Knight\\001.Idle\\001-00-007.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\\Knight\\001.Idle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\\Knight\\056.Walk", Vector2::Zero, 0.1f);

		mAnimator->Play(L"Knight001.Idle", true);

		mState = ePlayerState::Idle;

		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::Player::ePlayerState::Idle:
			idle();

		case ya::Player::ePlayerState::Walk:
			walk();
			break;

		case ya::Player::ePlayerState::Slash:
			slash();
			break;

		default:
			break;
		}
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		/*
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		// BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
		*/

	}

	void Player::Release()
	{
		GameObject::Release();

	}

	void Player::idle()
	{
		if (Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = ePlayerState::Walk;
			mAnimator->Play(L"Knight056.Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::Slash;
			// mAnimator->Play(L"", true);

		}
	}

	void Player::walk()
	{
		if (Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::D)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::W))
		{
			mState = ePlayerState::Idle;
			mAnimator->Play(L"Knight001.Idle", true);
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
			pos.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			pos.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::S))
			pos.y += 100.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}

	void Player::slash()
	{
		Transform* tr = GetComponent<Transform>();

		if (Input::GetKeyUp(eKeyCode::K))
		{
			mState = ePlayerState::Idle;
			mAnimator->Play(L"Knight001.Idle", true);
		}

		if (Input::GetKey(eKeyCode::K))
		{
			Scene* curScene = SceneManager::GetActiveScene();
			SlashEffect* slash = new SlashEffect();
			slash->Initialize();
			slash->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObject(slash, eLayerType::Effect);

		}

		// slash 끝나면 idle 상태로 돌아가야 함

	}

	void Player::slashAlt()
	{

	}

	
	
}