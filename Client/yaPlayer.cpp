#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "mySlashEffectLeft.h"
#include "yaSlashEffectRight.h"
#include "yaUpSlashEffect.h"
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

		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\right", Vector2::Zero, 0.1f); 
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_UpSlash\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Knight_Slashleft") = std::bind(&Player::SlashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Slashright") = std::bind(&Player::SlashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltleft") = std::bind(&Player::SlashAltEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltright") = std::bind(&Player::SlashAltEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_UpSlashneutral") = std::bind(&Player::UpSlashEndEvent, this);

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
		Transform* tr = GetComponent<Transform>();

		// 좌우 이동키 입력시 Walk 상태로 변경
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
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

		/*
		// 중립상태에서 W + 공격키 누르면 UpSlash
		if (Input::GetKeyDown(eKeyCode::K) && Input::GetKey(eKeyCode::W))
		{
			mState = ePlayerState::UpSlash;

			mAnimator->Play(L"Knight_UpSlash", true);

			Scene* curScene = SceneManager::GetActiveScene();
			UpSlashEffect* upSlashEffect = new UpSlashEffect();
			upSlashEffect->Initialize();
			upSlashEffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, -60.0f));
			curScene->AddGameObject(upSlashEffect, eLayerType::Effect);

		}
		*/

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::Slash;

			if (direction == 0)
			{
				mAnimator->Play(L"Knight_Slashleft", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectLeft* slasheffect = new SlashEffectLeft();
				slasheffect->Initialize();
				slasheffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-60.0f, 0.0f));
				curScene->AddGameObject(slasheffect, eLayerType::Effect);
			}
			else
			{
				mAnimator->Play(L"Knight_Slashright", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectRight* slasheffect = new SlashEffectRight();
				slasheffect->Initialize();
				slasheffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(60.0f, 0.0f));
				curScene->AddGameObject(slasheffect, eLayerType::Effect);
			}
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
		
		if (Input::GetKeyDown(eKeyCode::A))
			direction = 0;
		if (Input::GetKeyDown(eKeyCode::D))
			direction = 1;

		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::SlashAlt;

			if (direction == 0)
			{
				mAnimator->Play(L"Knight_SlashAltleft", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectLeft* slash = new SlashEffectLeft();
				slash->Initialize();
				slash->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-60.0f, 0.0f));
				curScene->AddGameObject(slash, eLayerType::Effect);
			}
			else
			{
				mAnimator->Play(L"Knight_SlashAltright", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectRight* slash = new SlashEffectRight();
				slash->Initialize();
				slash->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(60.0f, 0.0f));
				curScene->AddGameObject(slash, eLayerType::Effect);
			}
		}
	}

	void Player::slashAlt()
	{
		Transform* tr = GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::A))
			direction = 0;
		if (Input::GetKeyDown(eKeyCode::D))
			direction = 1;

		if (Input::GetKey(eKeyCode::K))
		{
			if (direction == 0)
			{
				mAnimator->Play(L"Knight_SlashAltleft", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectLeft* slash = new SlashEffectLeft();
				slash->Initialize();
				slash->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-60.0f, 0.0f));
				curScene->AddGameObject(slash, eLayerType::Effect);
			}
			else
			{
				mAnimator->Play(L"Knight_SlashAltright", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectRight* slash = new SlashEffectRight();
				slash->Initialize();
				slash->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(60.0f, 0.0f));
				curScene->AddGameObject(slash, eLayerType::Effect);
			}
		}
	}

	void Player::upSlash()
	{
		Transform* tr = GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::A))
			direction = 0;
		if (Input::GetKeyDown(eKeyCode::D))
			direction = 1;
	}

	void Player::SlashEndEvent()
	{
		mState = ePlayerState::Idle;
		if (direction == 0)
			mAnimator->Play(L"Knight_Idleleft", true);
		else
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::SlashAltEndEvent()
	{
		mState = ePlayerState::Idle;
		if (direction == 0)
			mAnimator->Play(L"Knight_Idleleft", true);
		else
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::UpSlashEndEvent()
	{
		mState = ePlayerState::Idle;
		if (direction == 0)
			mAnimator->Play(L"Knight_Idleleft", true);
		else
			mAnimator->Play(L"Knight_Idleright", true);
	}
}