#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "mySlashEffectLeft.h"
#include "yaSlashEffectRight.h"
#include "yaSlashAltEffectLeft.h"
#include "yaSlashAltEffectRight.h"
#include "yaUpSlashEffect.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"

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

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\right", Vector2::Zero, 0.05f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\right", Vector2::Zero, 0.05f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Dash\\left", Vector2::Zero, 0.025f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Dash\\right", Vector2::Zero, 0.025f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\right", Vector2::Zero, 0.05f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\right", Vector2::Zero, 0.05f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_UpSlash\\neutral", Vector2::Zero, 0.05f);
		
		mAnimator->GetCompleteEvent(L"Knight_Slashleft") = std::bind(&Player::SlashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Slashright") = std::bind(&Player::SlashEndEvent, this);

		mAnimator->GetCompleteEvent(L"Knight_SlashAltleft") = std::bind(&Player::SlashAltEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltright") = std::bind(&Player::SlashAltEndEvent, this);

		mAnimator->GetCompleteEvent(L"Knight_UpSlashneutral") = std::bind(&Player::UpSlashEndEvent, this);

		mAnimator->GetCompleteEvent(L"Knight_Dashleft") = std::bind(&Player::DashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Dashright") = std::bind(&Player::DashEndEvent, this);

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

		case ya::Player::ePlayerState::SlashAlt:
			slashAlt();
			break;

		case ya::Player::ePlayerState::UpSlash:
			upSlash();
			break;

		case ya::Player::ePlayerState::Dash:
			dash();
			break;

		case ya::Player::ePlayerState::Jump:
			jump();
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

	void Player::OnCollisionEnter(Collider* other)
	{

	}

	void Player::OnCollisionStay(Collider* other)
	{

	}

	void Player::OnCollisionExit(Collider* other)
	{

	}

	void Player::idle()
	{
		Transform* tr = GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::A))
			mDirection = eDirection::Left;
		if (Input::GetKeyDown(eKeyCode::D))
			mDirection = eDirection::Right;

		// �¿� �̵�Ű �Է½� Walk ���·� ����
		if (Input::GetKey(eKeyCode::A) || Input::GetKey(eKeyCode::D))
		{
			mState = ePlayerState::Walk;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Walkleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Walkright", true);

			return;
		}

		// ���Ű �Է½� dash ���·� ����
		if (Input::GetKeyDown(eKeyCode::L))
		{
			mState = ePlayerState::Dash;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Dashleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Dashright", true);

			return;
		}

		// W + ����Ű ������ UpSlash
		if (Input::GetKeyDown(eKeyCode::K) && Input::GetKey(eKeyCode::W))
		{
			mState = ePlayerState::UpSlash;

			mAnimator->Play(L"Knight_UpSlashneutral", true);

			Scene* curScene = SceneManager::GetActiveScene();
			UpSlashEffect* upSlashEffect = new UpSlashEffect();
			upSlashEffect->Initialize();
			upSlashEffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, -60.0f));
			curScene->AddGameObject(upSlashEffect, eLayerType::Effect);

			return;
		}

		// ���� �Է½� Slash ���� ����
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::Slash;

			
			if (mDirection == eDirection::Left)
			{
				mAnimator->Play(L"Knight_Slashleft", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectLeft* slashEffect = new SlashEffectLeft();
				slashEffect->Initialize();
				slashEffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-60.0f, 0.0f));
				curScene->AddGameObject(slashEffect, eLayerType::Effect);
			}

			else if (mDirection == eDirection::Right)
			{
				mAnimator->Play(L"Knight_Slashright", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectRight* slashEffect = new SlashEffectRight();
				slashEffect->Initialize();
				slashEffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(60.0f, 0.0f));
				curScene->AddGameObject(slashEffect, eLayerType::Effect);
			}
			
			return;
		}
	}

	void Player::walk()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKeyDown(eKeyCode::A))
			mDirection = eDirection::Left;
		else if (Input::GetKeyDown(eKeyCode::D))
			mDirection = eDirection::Right;

		/*
		// ���׽�Ʈ
		if (mAnimator->IsComplte())
		{
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Walkleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Walkright", true);
		}
		*/
		
		

		// �̵�Ű���� ���� �� ��� Idle���·� ����
		if (Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::D))
		{
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);

			return;
		}

		// ���Ű �Է½� dash ���·� ����
		if (Input::GetKeyDown(eKeyCode::L))
		{
			mState = ePlayerState::Dash;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Dashleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Dashright", true);

			return;
		}

		// W + ����Ű ������ UpSlash
		if (Input::GetKeyDown(eKeyCode::K) && Input::GetKey(eKeyCode::W))
		{
			mState = ePlayerState::UpSlash;

			mAnimator->Play(L"Knight_UpSlashneutral", true);

			Scene* curScene = SceneManager::GetActiveScene();
			UpSlashEffect* upSlashEffect = new UpSlashEffect();
			upSlashEffect->Initialize();
			upSlashEffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, -60.0f));
			curScene->AddGameObject(upSlashEffect, eLayerType::Effect);

			return;
		}

		// ���� �Է½� Slash ���� ����
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::Slash;

			if (mDirection == eDirection::Left)
			{
				mAnimator->Play(L"Knight_Slashleft", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectLeft* slasheffect = new SlashEffectLeft();
				slasheffect->Initialize();
				slasheffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-60.0f, 0.0f));
				curScene->AddGameObject(slasheffect, eLayerType::Effect);
			}
			else if (mDirection == eDirection::Right)
			{
				mAnimator->Play(L"Knight_Slashright", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectRight* slasheffect = new SlashEffectRight();
				slasheffect->Initialize();
				slasheffect->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(60.0f, 0.0f));
				curScene->AddGameObject(slasheffect, eLayerType::Effect);
			}

			return;
		}

		if (Input::GetKey(eKeyCode::A))
			pos.x -= 200.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			pos.x += 200.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}

	void Player::slash()
	{
		Transform* tr = GetComponent<Transform>();
		
		if (Input::GetKeyDown(eKeyCode::A))
			mDirection = eDirection::Left;
		if (Input::GetKeyDown(eKeyCode::D))
			mDirection = eDirection::Right;

		// slash ���¿��� �ѹ� �� ���ݽ� slashAlt ���� ����
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::SlashAlt;

			if (mDirection == eDirection::Left)
			{
				mAnimator->Play(L"Knight_SlashAltleft", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashAltEffectLeft* slashAltEffectLeft = new SlashAltEffectLeft();
				slashAltEffectLeft->Initialize();
				slashAltEffectLeft->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-60.0f, 0.0f));
				curScene->AddGameObject(slashAltEffectLeft, eLayerType::Effect);
			}
			else if (mDirection == eDirection::Right)
			{
				mAnimator->Play(L"Knight_SlashAltright", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashAltEffectRight* slashAltEffectRight = new SlashAltEffectRight();
				slashAltEffectRight->Initialize();
				slashAltEffectRight->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(60.0f, 0.0f));
				curScene->AddGameObject(slashAltEffectRight, eLayerType::Effect);
			}

			return;
		}
	}

	void Player::slashAlt()
	{
		Transform* tr = GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::A))
			mDirection = eDirection::Left;
		if (Input::GetKeyDown(eKeyCode::D))
			mDirection = eDirection::Right;

		// slashAlt ���¿��� �ѹ� �� ���ݽ� slash ���·� ����
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = ePlayerState::Slash;

			if (mDirection == eDirection::Left)
			{
				mAnimator->Play(L"Knight_Slashleft", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectLeft* slashEffectLeft = new SlashEffectLeft();
				slashEffectLeft->Initialize();
				slashEffectLeft->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-60.0f, 0.0f));
				curScene->AddGameObject(slashEffectLeft, eLayerType::Effect);
			}
			else if (mDirection == eDirection::Right)
			{
				mAnimator->Play(L"Knight_Slashright", true);

				Scene* curScene = SceneManager::GetActiveScene();
				SlashEffectRight* slashEffectRight = new SlashEffectRight();
				slashEffectRight->Initialize();
				slashEffectRight->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(60.0f, 0.0f));
				curScene->AddGameObject(slashEffectRight, eLayerType::Effect);
			}

			return;
		}
	}

	void Player::upSlash()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::D))
			mDirection = eDirection::Right;

		/*
		// upSlash ���¿����� �¿�� �̵� ����
		if (Input::GetKey(eKeyCode::A))
			pos.x -= 200.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			pos.x += 200.0f * Time::DeltaTime();
		

		tr->SetPos(pos);
		*/
	}

	void Player::dash()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		/*
		if (Input::GetKeyDown(eKeyCode::A))
			mDirection = eDirection::Left;
		else if (Input::GetKeyDown(eKeyCode::D))
			mDirection = eDirection::Right;
		*/

		if (mDirection == eDirection::Left)
		{
			pos.x -= 800.0f * Time::DeltaTime();
		}

		else if (mDirection == eDirection::Right)
		{
			pos.x += 800.0f * Time::DeltaTime();
		}

		tr->SetPos(pos);
	}

	void Player::jump()
	{

	}

	void Player::fall()
	{

	}

	void Player::SlashEndEvent()
	{
		mState = ePlayerState::Idle;
		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
		
	}

	void Player::SlashAltEndEvent()
	{
		mState = ePlayerState::Idle;
		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::UpSlashEndEvent()
	{
		mState = ePlayerState::Idle;
		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::DashEndEvent()
	{
		mState = ePlayerState::Idle;
		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}
}