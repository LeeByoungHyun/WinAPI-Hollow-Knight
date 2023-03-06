#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaSlashEffect.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"

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
		Transform* tr = GetComponent<Transform>();
		tr->SetName(L"PlayerTransform");
		//tr->SetPos(Vector2(400.0f, 400.0f));

		mAnimator = AddComponent<Animator>();
		//mAnimator->CreateAnimations(L"..\\Resources\\\Knight\\001.Idle", Vector2::Zero, 0.1f);
		//mAnimator->CreateAnimations(L"..\\Resources\\\Knight\\056.Walk", Vector2::Zero, 0.1f);
		//mAnimator->CreateAnimations(L"..\\Resources\\\Knight\\006.Slash", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\right", Vector2::Zero, 0.1f); 
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\right", Vector2::Zero, 0.1f);

		mAnimator->Play(L"Knight_Idleright", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetName(L"PlayerCollider");
		mCollider->SetCenter(Vector2(-30.0f, -100.0f));
		mCollider->SetSize(Vector2(60.0f, 100.0f));

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
			break;

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
			if (Input::GetKeyDown(eKeyCode::A))
				direction = 0;
			if (Input::GetKeyDown(eKeyCode::D))
				direction = 1;
			
			mState = ePlayerState::Walk;
			if (direction == 0)
				mAnimator->Play(L"Knight_Walkleft", true);
			else
				mAnimator->Play(L"Knight_Walkright", true);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::Slash;
			if (direction == 0)
				mAnimator->Play(L"Knight_Slashleft", true);
			else
				mAnimator->Play(L"Knight_Slashright", true);
		}
	}

	void Player::walk()
	{
		if (Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::D)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::W))
		{
			if (Input::GetKeyDown(eKeyCode::A))
				direction = 0;
			if (Input::GetKeyDown(eKeyCode::D))
				direction = 1;

			mState = ePlayerState::Idle;
			if (direction == 0)
				mAnimator->Play(L"Knight_Idleleft", true);
			else
				mAnimator->Play(L"Knight_Idleright", true);
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
			if (direction == 0)
				mAnimator->Play(L"Knight_Idleleft", true);
			else
				mAnimator->Play(L"Knight_Idleright", true);
		}
		
		if (Input::GetKeyDown(eKeyCode::A))
			direction = 0;
		if (Input::GetKeyDown(eKeyCode::D))
			direction = 1;

		if (Input::GetKey(eKeyCode::K))
		{
			if (direction == 0)
				mAnimator->Play(L"Knight_Slashleft", true);
			else
				mAnimator->Play(L"Knight_Slashright", true);

			Scene* curScene = SceneManager::GetActiveScene();
			SlashEffect* slash = new SlashEffect();
			slash->Initialize();
			slash->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-30.0f, 0.0f));
			curScene->AddGameObject(slash, eLayerType::Effect);
		}

		// slash 끝나면 idle 상태로 돌아가야 함

	}

	void Player::slashAlt()
	{

	}

	
	
}