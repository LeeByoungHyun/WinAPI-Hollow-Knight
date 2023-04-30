#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaRigidBody.h"
#include "yaCamera.h"
#include "yaSound.h"

#include "DownSlashEffect.h"
#include "yaUpSlashEffect.h"
#include "yaDashEffectLeft.h"
#include "yaDashEffectRight.h"
#include "FireballEffectLeft.h"
#include "FireballEffectRight.h"
#include "PlayerSkull.h"
#include "FocusEffect.h"
#include "DoubleJumpEffect.h"
#include "FireballCastEffect.h"
#include "FireballCastEffectLeft.h"
#include "FireballCastEffectRight.h"
#include "SlashEffect.h"
#include "SlashAltEffect.h"
#include "Fade.h"
#include "SoulUI.h"
#include "HitCrackEffect.h"
#include "StunEffect.h"

namespace ya
{
	// 싱글톤 객체 초기화
	Player* Player::instance = nullptr;

	Player::Player()
	{
		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mRigidBody = AddComponent<RigidBody>();
		curScene = SceneManager::GetActiveScene();

		hp = 5;
		neilAtk = 9;
		spellAtk = 15;
		deathFlag = false;
		invincibilityFlag = false;
	}

	Player::~Player()
	{

	}

	void Player::Initialize()
	{
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Run\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Run\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Dash\\left", Vector2::Zero, 0.025f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Dash\\right", Vector2::Zero, 0.025f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\left", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\right", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\left", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\right", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_UpSlash\\neutral", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DownSlash\\neutral", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballCast\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballCast\\right", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Recoil\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Recoil\\right", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Spike\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Spike\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Stun\\left", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Stun\\right", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Death\\neutral", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Focus\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Focus\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusEnd\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusEnd\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusGet\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusGet\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusGetOnce\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusGetOnce\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Airborne\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Airborne\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Fall\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Fall\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DoubleJump\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DoubleJump\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Enter\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_WakeUp\\neutral", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_WallSlide\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_WallSlide\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_WallJump\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_WallJump\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Challenge\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Knight_Slashleft") = std::bind(&Player::slashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Slashright") = std::bind(&Player::slashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltleft") = std::bind(&Player::slashAltEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltright") = std::bind(&Player::slashAltEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_UpSlashneutral") = std::bind(&Player::upSlashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_DownSlashneutral") = std::bind(&Player::downSlashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Dashleft") = std::bind(&Player::dashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Dashright") = std::bind(&Player::dashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Recoilleft") = std::bind(&Player::recoilEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Recoilright") = std::bind(&Player::recoilEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Deathneutral") = std::bind(&Player::deathEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Focusleft") = std::bind(&Player::focusEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Focusright") = std::bind(&Player::focusEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FocusEndleft") = std::bind(&Player::focusEndEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FocusEndright") = std::bind(&Player::focusEndEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FocusGetleft") = std::bind(&Player::focusGetEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FocusGetright") = std::bind(&Player::focusGetEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FocusGetOnceleft") = std::bind(&Player::focusGetOnceEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FocusGetOnceright") = std::bind(&Player::focusGetOnceEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FireballCastleft") = std::bind(&Player::castFireballEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FireballCastright") = std::bind(&Player::castFireballEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_DoubleJumpleft") = std::bind(&Player::doubleJumpEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_DoubleJumpright") = std::bind(&Player::doubleJumpEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Enterneutral") = std::bind(&Player::enterComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_WakeUpneutral") = std::bind(&Player::wakeUpCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_WallJumpleft") = std::bind(&Player::wallJumpCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_WallJumpright") = std::bind(&Player::wallJumpCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Challengeneutral") = std::bind(&Player::challengeComplateEvent, this);

		walkSound = ResourceManager::Load<Sound>(L"knightWalk", L"..\\Resources\\Sound\\Knight\\Knight Walk.wav");
		damageSound = ResourceManager::Load<Sound>(L"Knight_damage", L"..\\Resources\\Sound\\Knight\\Knight_damage.wav");
		dashSound = ResourceManager::Load<Sound>(L"Knight_dash", L"..\\Resources\\Sound\\Knight\\Knight_dash.wav");
		doubleJumpSound = ResourceManager::Load<Sound>(L"Knight_doubleJump", L"..\\Resources\\Sound\\Knight\\Knight_doubleJump.wav");
		fireballSound = ResourceManager::Load<Sound>(L"Knight_fireball", L"..\\Resources\\Sound\\Knight\\Knight_fireball.wav");
		jumpSound = ResourceManager::Load<Sound>(L"Knight_jump", L"..\\Resources\\Sound\\Knight\\Knight_jump.wav");
		landSound = ResourceManager::Load<Sound>(L"Knight_land_soft", L"..\\Resources\\Sound\\Knight\\Knight_land_soft.wav");
		focusChargeSound = ResourceManager::Load<Sound>(L"Knight_focus_charging", L"..\\Resources\\Sound\\Knight\\Knight_focus_charging.wav");
		focusSuccessSound = ResourceManager::Load<Sound>(L"Knight_focus_Success", L"..\\Resources\\Sound\\Knight\\Knight_focus_Success.wav");
		slash1Sound = ResourceManager::Load<Sound>(L"sword_1", L"..\\Resources\\Sound\\Knight\\sword_1.wav");
		slash2Sound = ResourceManager::Load<Sound>(L"sword_2", L"..\\Resources\\Sound\\Knight\\sword_2.wav");
		slash3Sound = ResourceManager::Load<Sound>(L"sword_3", L"..\\Resources\\Sound\\Knight\\sword_3.wav");
		slash4Sound = ResourceManager::Load<Sound>(L"sword_4", L"..\\Resources\\Sound\\Knight\\sword_4.wav");
		slash5Sound = ResourceManager::Load<Sound>(L"sword_5", L"..\\Resources\\Sound\\Knight\\sword_5.wav");
		challengeSound = ResourceManager::Load<Sound>(L"challenge", L"..\\Resources\\Sound\\Knight\\hero_challenge.wav");

		mAnimator->Play(L"Knight_Idleright", true);
		
		mCollider->SetName(L"PlayerCollider");
		mCollider->SetCenter(Vector2(-30.0f, -120.0f));
		mCollider->SetSize(Vector2(60.0f, 120.0f));

		mRigidBody->SetMass(1.0f);
		mRigidBody->SetGravity(Vector2(0.0f, 2000.0f));
		mState = ePlayerState::Idle;

		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		curScene = SceneManager::GetActiveScene();
		tr = GetComponent<Transform>();

		// HP가 0이하가 되면 죽음
		if (hp <= 0)
		{
			mState = ePlayerState::Death;
		}

		// 'L' 누르면 무적모드 다시 누르면 해제
		if (Input::GetKeyDown(eKeyCode::L))
		{
			if (invincibilityFlag == false)
				invincibilityFlag = true;
			else
				invincibilityFlag = false;
		}

		// 현재 상태가 특정 상태가 아니고 onGround = true 가 아닐 경우 fall 상태로 
		if (mRigidBody->GetGround() == false)
		{
			if ((mState != ePlayerState::Dash) && (mState != ePlayerState::Jump) 
				&& (mState != ePlayerState::DoubleJump) && (mState != ePlayerState::Recoil)
				&& (mState != ePlayerState::Slash) && (mState != ePlayerState::SlashAlt)
				&& (mState != ePlayerState::UpSlash) && (mState != ePlayerState::CastFireball)
				&& (mState != ePlayerState::DownSlash) && (mState != ePlayerState::Spike)
				&& (mState != ePlayerState::Death) && (mState != ePlayerState::WallSlide)
				&& (mState != ePlayerState::WallJump))
			{
				mState = ePlayerState::Fall;
				idleFlag = false;
			}
		}

		if (mState != ePlayerState::Walk)
			walkSound->Stop(true);

		// 좌우이동 멈추면 rigidbody 속도 0으로
		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKeyUp(eKeyCode::LEFT))
			velocity.x = 0.0f;
		if (Input::GetKeyUp(eKeyCode::RIGHT))
			velocity.x = 0.0f;
		mRigidBody->SetVelocity(velocity);

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

		case ya::Player::ePlayerState::DownSlash:
			downSlash();
			break;

		case ya::Player::ePlayerState::Dash:
			dash();
			break;

		case ya::Player::ePlayerState::Jump:
			jump();
			break; 
		
		case ya::Player::ePlayerState::DoubleJump:
			doubleJump();
			break;

		case ya::Player::ePlayerState::Fall:
			fall();
			break;

		case ya::Player::ePlayerState::Recoil:
			recoil();
			break;

		case ya::Player::ePlayerState::Spike:
			spike();
			break;

		case ya::Player::ePlayerState::Death:
			death();
			break;

		case ya::Player::ePlayerState::Focus:
			focus();
			break;

		case ya::Player::ePlayerState::FocusEnd:
			focusEnd();
			break;

		case ya::Player::ePlayerState::FocusGet:
			focusGet();
			break;

		case ya::Player::ePlayerState::FocusGetOnce:
			focusGetOnce();
			break;

		case ya::Player::ePlayerState::CastFireball:
			castFireball();
			break;

		case ya::Player::ePlayerState::Enter:
			enter();
			break;

		case ya::Player::ePlayerState::WakeUp:
			wakeUp();
			break;

		case ya::Player::ePlayerState::WallSlide:
			wallSlide();
			break;

		case ya::Player::ePlayerState::WallJump:
			wallJump();
			break;

		case ya::Player::ePlayerState::Challenge:
			challenge();
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
		eLayerType otherType = other->GetOwner()->GetType();	// 플레이어와 충돌한 객체의 타입
		if (mState != ePlayerState::Death)
		{
			switch (otherType)
			{
			case eLayerType::Monster:
				if (!invincibilityFlag)
				{
					mState = ePlayerState::Recoil;
					recoilFlag = false;
					stunFlag = false;
				}
				break;
			case eLayerType::FalseKnight:
				if (!invincibilityFlag)
				{
					mState = ePlayerState::Recoil;
					recoilFlag = false;
					stunFlag = false;
				}
				break;
			case eLayerType::Hornet:
				if (!invincibilityFlag)
				{
					mState = ePlayerState::Recoil;
					recoilFlag = false;
					stunFlag = false;
				}
				break;

			// 충돌한 객체가 땅일 경우 idle
			case eLayerType::Ground:
				if (mState != ePlayerState::Spike)
				{
					mState = ePlayerState::Idle;
					if (mDirection == eDirection::Left)
						mAnimator->Play(L"Knight_Idleleft", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"Knight_Idleright", true);

					mRigidBody->SetGround(true);
					landSound->Play(false);
				}
				else
				{
					mRigidBody->SetGround(true);
				}
				
				break;

				// spike
			case eLayerType::Spike:
				mState = ePlayerState::Spike;
				spikeFlag = false;
				break;
			}
		}

		GameObject::OnCollisionEnter(other);
	}

	void Player::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void Player::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
		eLayerType otherType = other->GetOwner()->GetType();	// 플레이어와 충돌한 객체의 타입

		switch (otherType)
		{
		case eLayerType::Wall:
			if (mState == ePlayerState::WallSlide)
			{
				mState = ePlayerState::Fall;
			}
			break;
		}
	}

	void Player::idle()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (idleFlag == false)
		{
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);

			mRigidBody->SetVelocity(Vector2::Zero);
			idleFlag = true;
			
			mRigidBody->SetActive(true);
			initializeFlag();

			Vector2 velocity = mRigidBody->GetVelocity();
			velocity.x = 0.0f;
			mRigidBody->SetVelocity(velocity);
		}
		
		// 좌우 이동키 입력시 Walk 상태로 변경
		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Walk;
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Walkleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Walkright", true);
			idleFlag = false;

			// sound
			walkSound->Play(true);

			return;
		}

		// Z 입력시 점프
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = ePlayerState::Jump;
			idleFlag = false;
			return;
		}

		// 대시키 입력시 dash 상태로 변경
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			idleFlag = false;
			return;
		}

		// up + 공격키 누르면 UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			idleFlag = false;
			return;
		}

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			idleFlag = false;
			return;
		}

		// S 입력시 원거리 공격
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (SoulUI::GetInstance()->GetSoul() < 30)
				return;

			mState = ePlayerState::CastFireball;
			idleFlag = false;
			return;
		}

		// A 입력시 체력회복
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (SoulUI::GetInstance()->GetSoul() <= 0.0f)
				return;

			mState = ePlayerState::Focus;
			idleFlag = false;
			return;
		}
	}

	void Player::walk()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		// 이동키에서 손을 땔 경우 Idle상태로 변경
		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);

			walkSound->Stop(true);
			return;
		}

		// 대시키 입력시 dash 상태로 변경
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			walkSound->Stop(true);
			return;
		}

		// Z 입력시 점프
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = ePlayerState::Jump;
			walkSound->Stop(true);
			return;
		}

		// up + 공격키 누르면 UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			walkSound->Stop(true);
			return;
		}

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			walkSound->Stop(true);
			return;
		}

		// S 입력시 원거리 공격
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (SoulUI::GetInstance()->GetSoul() < 30)
				return;

			mState = ePlayerState::CastFireball;
			walkSound->Stop(true);
			return;
		}

		// A 입력시 체력회복
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (SoulUI::GetInstance()->GetSoul() <= 0.0f)
				return;

			mState = ePlayerState::Focus;
			walkSound->Stop(true);
			return;
		}

		/*
		Vector2 pos = tr->GetPos();
		if (Input::GetKey(eKeyCode::LEFT))
			pos.x -= 300.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::RIGHT))
			pos.x += 300.0f * Time::DeltaTime();
		tr->SetPos(pos);
		*/
		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::slash()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (slashFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_Slashleft", true);
				slashFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Slashright", true);
				slashFlag = true;
				break;

			default:
				break;
			}
			object::Instantiate<SlashEffect>(eLayerType::NeilEffect);
			slash1Sound->Play(false);
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.25f)
		{
			// up + 공격키 누르면 UpSlash
			if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
			{
				mState = ePlayerState::UpSlash;
				mTime = 0.0f;
				slashFlag = false;
				return;
			}

			// slash 상태에서 한번 더 공격시 slashAlt 상대로 변경
			if (Input::GetKeyDown(eKeyCode::X))
			{
				mState = ePlayerState::SlashAlt;
				mTime = 0.0f;
				slashFlag = false;
				return;
			}
		}

		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::slashAlt()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (slashAltFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_SlashAltleft", true);
				slashAltFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_SlashAltright", true);
				slashAltFlag = true;
				break;

			default:
				break;
			}
			object::Instantiate<SlashAltEffect>(eLayerType::NeilEffect);
			slash2Sound->Play(false);
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.25f)
		{
			// up + 공격키 누르면 UpSlash
			if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
			{
				mState = ePlayerState::UpSlash;
				mTime = 0.0f;
				slashAltFlag = false;
				return;
			}

			// slashAlt 상태에서 한번 더 공격시 slash 상태로 변경
			if (Input::GetKeyDown(eKeyCode::X))
			{
				mState = ePlayerState::Slash;
				mTime = 0.0f;
				slashAltFlag = false;
				return;
			}
		}

		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::upSlash()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (upSlashFlag == false)
		{
			mAnimator->Play(L"Knight_UpSlashneutral", true);
			object::Instantiate<UpSlashEffect>(eLayerType::NeilEffect);
			slash3Sound->Play(false);
			upSlashFlag = true;
		}

		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::downSlash()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (downSlashFlag == false)
		{
			mAnimator->Play(L"Knight_DownSlashneutral", true);
			object::Instantiate<DownSlashEffect>(eLayerType::NeilEffect);
			slash4Sound->Play(false);
			downSlashFlag = true;
		}

		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::dash()
	{
		if (dashFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_Dashleft", false);
				object::Instantiate<DashEffectLeft>(tr->GetPos() + Vector2(130.0f, 30.0f), eLayerType::BackEffect);
				dashFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Dashright", false);
				object::Instantiate<DashEffectRight>(tr->GetPos() + Vector2(-130.0f, 30.0f), eLayerType::BackEffect);
				dashFlag = true;
				break;

			default:
				break;
			}

			dashSound->Play(false);
		}

		mRigidBody->SetVelocity((Vector2::Zero));
		Vector2 velocity = mRigidBody->GetVelocity();
		if (mDirection == eDirection::Left)
		{
			velocity.x = -800.0f;
			velocity.y = -10.0f;
		}
		if (mDirection == eDirection::Right)
		{
			velocity.x = 800.0f;
			velocity.y = -10.0f;
		}
		mRigidBody->SetVelocity(velocity);
	}

	void Player::jump()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (jumpFlag == false)
		{
			jumpSound->Play(false);
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_Airborneleft", false);
				jumpFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Airborneright", false);
				jumpFlag = true;
				break;

			default:
				break;
			}

			// 점프 물리가속도 설정
			Vector2 velocity = mRigidBody->GetVelocity();
			velocity.y -= 900.0f;
			mRigidBody->SetVelocity(velocity);
			mRigidBody->SetGround(false);
		}

		// 한번 더 점프키 입력시 더블점프
		if (Input::GetKeyDown(eKeyCode::Z) && doubleJumpFlag == false)
		{
			mState = ePlayerState::DoubleJump;
			jumpFlag = false;
			return;
		}

		// 대시키 입력시 dash 상태로 변경
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			jumpFlag = false;
			return;
		}

		// up + 공격키 누르면 UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			jumpFlag = false;
			return;
		}

		// down + 공격 입력시 DownSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownSlash;
			jumpFlag = false;
			return;
		}

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			jumpFlag = false;
			return;
		}

		// S 입력시 원거리 공격
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (SoulUI::GetInstance()->GetSoul() < 30)
				return;

			mState = ePlayerState::CastFireball;
			jumpFlag = false;
			return;
		}

		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::doubleJump()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (doubleJumpFlag == false)
		{
			DoubleJumpEffect* effect = object::Instantiate<DoubleJumpEffect>(tr->GetPos() + Vector2(0.0f, 0.0f), eLayerType::BackEffect);
			effect->GetComponent<Transform>()->SetSize(Vector2(0.5f, 0.5f));
			doubleJumpSound->Play(false);

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_DoubleJumpleft", false);
				doubleJumpFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_DoubleJumpright", false);
				doubleJumpFlag = true;
				break;

			default:
				break;
			}

			// 중력 초기화 해줘야 함
			// 점프 물리가속도 설정
			Vector2 velocity = mRigidBody->GetVelocity();
			velocity.y = -800.0f;
			mRigidBody->SetVelocity(velocity);
			mRigidBody->SetGround(false);
		}

		// 대시키 입력시 dash 상태로 변경
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			return;
		}

		// up + 공격키 누르면 UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			return;
		}

		// down + 공격 입력시 DownSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownSlash;
			return;
		}

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			return;
		}

		// S 입력시 원거리 공격
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (SoulUI::GetInstance()->GetSoul() < 30)
				return;

			mState = ePlayerState::CastFireball;
			return;
		}

		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::fall()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (fallFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_Fallleft", false);
				fallFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Fallright", false);
				fallFlag = true;
				break;

			default:
				break;
			}

			initializeFlag();
		}

		// 한번 더 점프키 입력시 더블점프
		if (Input::GetKeyDown(eKeyCode::Z) && doubleJumpFlag == false)
		{
			mState = ePlayerState::DoubleJump;
			fallFlag = false;
			return;
		}

		// 대시키 입력시 dash 상태로 변경
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			fallFlag = false;
			return;
		}

		// up + 공격키 누르면 UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			fallFlag = false;
			return;
		}

		// down + 공격 입력시 DownSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownSlash;
			fallFlag = false;
			return;
		}

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			fallFlag = false;
			return;
		}

		// S 입력시 원거리 공격
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (SoulUI::GetInstance()->GetSoul() < 30)
				return;

			mState = ePlayerState::CastFireball;
			fallFlag = false;
			return;
		}

		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::castFireball()
	{
		if (castFireballFlag == false)
		{
			object::Instantiate<FireballCastEffect>(tr->GetPos(), eLayerType::BackEffect);
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_FireballCastleft", false);
				object::Instantiate<FireballEffectLeft>(tr->GetPos(), eLayerType::SpellEffect);
				castFireballFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_FireballCastright", false);
				object::Instantiate<FireballEffectRight>(tr->GetPos(), eLayerType::SpellEffect);
				castFireballFlag = true;
				break;

			default:
				break;
			}
			fireballSound->Play(false);
			SoulUI::GetInstance()->SetSoul(SoulUI::GetInstance()->GetSoul() - 30.0f);
		}

		mRigidBody->SetVelocity((Vector2::Zero));
		Vector2 velocity = mRigidBody->GetVelocity();
		if (mDirection == eDirection::Left)
		{
			velocity.x = 30.0f;
			velocity.y = -10.0f;
		}
		if (mDirection == eDirection::Right)
		{
			velocity.x = -30.0f;
			velocity.y = -10.0f;
		}
		mRigidBody->SetVelocity(velocity);
	}

	void Player::recoil()
	{
		if (stunFlag == false)
		{
			invincibilityFlag = true;
			hp -= 1;	// 피격당한 오브젝트의 공격력 값을 가져와야함
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Stunleft", false);

			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Stunright", false);

			damageSound->Play(false);
			stunFlag = true;

			object::Instantiate<HitCrackEffect>(tr->GetPos(), eLayerType::BackEffect);
			object::Instantiate<StunEffect>(tr->GetPos(), eLayerType::BackEffect);
		}

		mTime += Time::DeltaTime();
		if (mTime < 0.2f)
		{
			mRigidBody->SetVelocity((Vector2::Zero));
		}

		if (mTime >= 0.2f)
		{
			if (recoilFlag == false)
			{
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"Knight_Recoilleft", false);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"Knight_Recoilright", false);
			}
			mRigidBody->SetGround(false);
			Vector2 velocity;
			if (mDirection == eDirection::Left)
				velocity = Vector2(200.0f, -200.0f);
			else if (mDirection == eDirection::Right)
				velocity = Vector2(-200.0f, -200.0f);

			mRigidBody->SetVelocity(velocity);
			recoilFlag = true;
		}
	}

	void Player::spike()
	{
		if (spikeFlag == false)
		{
			object::Instantiate<HitCrackEffect>(tr->GetPos(), eLayerType::BackEffect);
			object::Instantiate<StunEffect>(tr->GetPos(), eLayerType::BackEffect);
			invincibilityFlag = true;
			hp -= 1;	// 피격당한 오브젝트의 공격력 값을 가져와야함
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Spikeleft", false);

			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Spikeright", false);

			damageSound->Play(false);
			spikeFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime < 0.2f)
		{
			mRigidBody->SetVelocity((Vector2::Zero));
		}

		if (mTime >= 0.2f)
		{
			mRigidBody->SetGround(false);
			Vector2 velocity;
			if (mDirection == eDirection::Left)
				velocity = Vector2(200.0f, -200.0f);
			else if (mDirection == eDirection::Right)
				velocity = Vector2(-200.0f, -200.0f);

			Fade::GetInstance()->SetFadeColor(Fade::eColor::Black);
			Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeOut);

			mRigidBody->SetVelocity(velocity);
		}
	}

	void Player::death()
	{
		if (deathFlag == false)
		{
			mAnimator->Play(L"Knight_Deathneutral", false);
			mRigidBody->SetVelocity((Vector2::Zero));
			mRigidBody->SetActive(false);
			deathFlag = true;
		}

		

	}

	void Player::focus()
	{
		if (focusFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_Focusleft", false);
				focusFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Focusright", false);
				focusFlag = true;
				break;

			default:
				break;
			}
			object::Instantiate<FocusEffect>(tr->GetPos(), eLayerType::BackEffect);
			focusChargeSound->Play(false);
		}

		mRigidBody->SetVelocity(Vector2::Zero);

		if (SoulUI::GetInstance()->GetSoul() <= 0.0f)
		{
			focusFlag = false; 
			mState = ePlayerState::FocusEnd;
		}
		SoulUI::GetInstance()->SetSoul(SoulUI::GetInstance()->GetSoul() - 30.0f * Time::DeltaTime());

		// 회복키에서 손 때면 회복종료
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusFlag = false;
			mTime = 0.0f;
			return;
		}

		// 1초 이상 회복모션 유지 성공시
		mTime += Time::DeltaTime();
		if (mTime >= 1)
		{
			mState = ePlayerState::FocusGet;
			focusFlag = false;
			mTime = 0.0f;
			focusChargeSound->Stop(true);
			return;
		}
	}

	void Player::focusEnd()
	{
		if (focusEndFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_FocusEndleft", false);
				focusEndFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_FocusEndright", false);
				focusEndFlag = true;
				break;

			default:
				break;
			}
			focusChargeSound->Stop(true);
			focusSuccessSound->Stop(true);
		}
	}

	void Player::focusGet()
	{
		if (focusGetFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_FocusGetleft", false);
				focusGetFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_FocusGetright", false);
				focusGetFlag = true;
				break;

			default:
				break;
			}
			object::Instantiate<FocusEffect>(tr->GetPos(), eLayerType::BackEffect);
			hp += 1;
			focusSuccessSound->Play(false);
			focusChargeSound->Play(false);
		}

		if (SoulUI::GetInstance()->GetSoul() <= 0.0f)
		{
			focusFlag = false;
			mState = ePlayerState::FocusEnd;
		}
		SoulUI::GetInstance()->SetSoul(SoulUI::GetInstance()->GetSoul() - 30.0f * Time::DeltaTime());

		// 회복키에서 손 때면 회복종료
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusGetFlag = false;
			mTime = 0.0f;
			return;
		}

		// 1초 이상 회복모션 유지 성공시
		mTime += Time::DeltaTime();
		if (mTime >= 1)
		{
			mState = ePlayerState::FocusGet;
			focusGetFlag = false;
			mTime = 0.0f;
			focusSuccessSound->Stop(true);
			return;
		}
	}

	void Player::focusGetOnce()
	{
		if (focusGetOnceFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_FocusGetOnceleft", false);
				focusGetOnceFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_FocusGetOnceright", false);
				focusGetOnceFlag = true;
				break;

			default:
				break;
			}
			object::Instantiate<FocusEffect>(tr->GetPos(), eLayerType::BackEffect);
		}

		// 회복키에서 손 때면 회복종료
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusGetOnceFlag = false;
			mTime = 0.0f;
			return;
		}

		// 1초 이상 회복모션 유지 성공시
		mTime += Time::DeltaTime();
		if (mTime >= 1)
		{
			mState = ePlayerState::FocusGetOnce;
			focusGetOnceFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void Player::enter()
	{
		if (enterFlag == false)
		{
			mAnimator->Play(L"Knight_Enterneutral", false);
			enterFlag = true;
		}
	}

	void Player::wakeUp()
	{
		if (wakeUpFlag == false)
		{
			mDirection = eDirection::Right;
			mAnimator->Play(L"Knight_WakeUpneutral", false);
			wakeUpFlag = true;
		}
	}

	void Player::wallSlide()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (wallSlideFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_WallSlideleft", true);
				wallSlideFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_WallSlideright", true);
				wallSlideFlag = true;
				break;

			default:
				break;
			}
		}

		if (mRigidBody->GetGround() == true)
		{
			mState = ePlayerState::Idle;
		}

		// slide중 jump
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = ePlayerState::WallJump;
			wallSlideFlag = false;
			return;
		}
		Vector2 velocity = mRigidBody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -400.0f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 400.0f;
		velocity.y = 200.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::wallJump()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (wallJumpFlag == false)
		{
			Vector2 velocity = mRigidBody->GetVelocity();
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_WallJumpleft", false);
				mDirection = eDirection::Right;
				velocity.x = 400.0f;
				velocity.y = -700.0f;
				wallJumpFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_WallJumpright", false);
				mDirection = eDirection::Left;
				velocity.x = -400.0f;
				velocity.y = -700.0f;
				wallJumpFlag = true;
				break;

			default:
				break;
			}
			mRigidBody->SetVelocity(velocity);
			doubleJumpFlag = false;	// 벽점하면 더블점프 다시 가능
		}

		// 한번 더 점프키 입력시 더블점프
		if (Input::GetKeyDown(eKeyCode::Z) && doubleJumpFlag == false)
		{
			mState = ePlayerState::DoubleJump;
			jumpFlag = false;
			wallJumpFlag = false;
			return;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.1f)
		{
			Vector2 velocity = mRigidBody->GetVelocity();
			if (Input::GetKey(eKeyCode::LEFT))
				velocity.x = -400.0f;
			if (Input::GetKey(eKeyCode::RIGHT))
				velocity.x = 400.0f;
			mRigidBody->SetVelocity(velocity);
		}
		
	}

	void Player::challenge()
	{
		if (challengeFlag == false)
		{
			mDirection = eDirection::Right;
			mAnimator->Play(L"Knight_Challengeneutral", false);
			challengeFlag = true;
			//challengeSound->Play(false);
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.7f && challengeSoundFlag == false)
		{
			challengeSound->Play(false);
			challengeSoundFlag = true;
		}
	}

	void Player::slashEndEvent()
	{
		// 공중, 지상일 경우 구분
		switch (mRigidBody->GetGround())
		{
		case true:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;

		case false:
			mState = ePlayerState::Fall;
			break;

		default:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;
		}
	}

	void Player::slashAltEndEvent()
	{
		// 공중, 지상일 경우 구분
		switch (mRigidBody->GetGround())
		{
		case true:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;

		case false:
			mState = ePlayerState::Fall;
			break;

		default:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;
		}
	}

	void Player::upSlashEndEvent()
	{
		// 공중, 지상일 경우 구분
		switch (mRigidBody->GetGround())
		{
		case true:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;

		case false:
			mState = ePlayerState::Fall;
			break;

		default:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;
		}
	}

	void Player::downSlashEndEvent()
	{
		// 공중, 지상일 경우 구분
		switch (mRigidBody->GetGround())
		{
		case true:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;

		case false:
			mState = ePlayerState::Fall;
			break;

		default:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;
		}
	}

	void Player::recoilEndEvent()
	{
		recoilFlag = false;
		stunFlag = false;
		fallFlag = false;
		mTime = 0.0f;

		// 공중, 지상일 경우 구분
		switch (mRigidBody->GetGround())
		{
		case true:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;

		case false:
			mState = ePlayerState::Fall;
			break;

		default:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;
		}

		invincibilityFlag = false;
	}

	void Player::spikeCompleteEvent()
	{
	}

	void Player::dashEndEvent()
	{
		// 대쉬 끝나면 대쉬 재사용 가능하도록
		dashFlag = false;
		mRigidBody->SetVelocity(Vector2::Zero);

		// 대쉬 끝났을 때 공중, 지상일 경우 구분
		switch (mRigidBody->GetGround())
		{
		case true:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;

		case false:
			mState = ePlayerState::Fall;
			break;

		default:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;
		}
	}

	void Player::deathEndEvent()
	{
		//object::Destroy(this);
		Fade::GetInstance()->SetFadeColor(Fade::eColor::Black);
		Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeOut);
		this->SetState(eState::Pause);
		
		object::Instantiate<PlayerSkull>(tr->GetPos(), eLayerType::Player);
		// 위에 줄 삭제하고 플레이어 애니메이션을 하나 더 만들면 됨

		Camera::SetTarget(nullptr);
	}

	void Player::focusEndEvent()
	{
		
	}

	void Player::focusEndEndEvent()
	{
		mState = ePlayerState::Idle;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::focusGetEndEvent()
	{
		// 회복키가 계속 눌려있을 경우 이어서 회복
		if (Input::GetKey(eKeyCode::A))
		{
			mState = ePlayerState::FocusGetOnce;
			focusGetFlag = false;
			return;
		}

		// 아닐 경우 회복종료 모션으로 
		else
		{
			mState = ePlayerState::FocusEnd;
			focusGetFlag = false;
			return;
		}
	}

	void Player::focusGetOnceEndEvent()
	{
		
	}

	void Player::castFireballEndEvent()
	{
		// 공중, 지상일 경우 구분
		switch (mRigidBody->GetGround())
		{
		case true:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;

		case false:
			mState = ePlayerState::Fall;
			break;

		default:
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);
			break;
		}
	}

	void Player::doubleJumpEndEvent()
	{
		mState = ePlayerState::Fall;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Fallleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Fallright", true);
	}

	void Player::enterComplateEvent()
	{
		enterComplateFlag = true;
	}
	void Player::wakeUpCompleteEvent()
	{
		mState = ePlayerState::Idle;
		invincibilityFlag = false;
	}

	void Player::wallJumpCompleteEvent()
	{
		mState = ePlayerState::Fall;
		wallJumpFlag = false;
	}

	void Player::challengeComplateEvent()
	{
		challengeCompleteFlag = true;
	}

	void Player::initializeFlag()
	{
		//idleFlag = false;
		walkFlag = false;
		slashFlag = false;
		slashAltFlag = false;
		upSlashFlag = false;
		downSlashFlag = false;
		dashFlag = false;
		deathFlag = false;
		//invincibilityFlag = false;
		focusFlag = false;
		focusEndFlag = false;
		focusGetFlag = false;
		focusGetOnceFlag = false;
		castFireballFlag = false;
		jumpFlag = false;
		doubleJumpFlag = false;
		fallFlag = false;
		stunFlag = false;
		recoilFlag = false;
		enterFlag = false;
		enterComplateFlag = false;
		spikeFlag = false;
		wakeUpFlag = false;
		wallSlideFlag = false;
		wallJumpFlag = false;
		mTime = 0.0f;
	}
}
