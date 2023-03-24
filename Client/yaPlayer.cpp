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

namespace ya
{
	// �̱��� ��ü �ʱ�ȭ
	Player* Player::instance = nullptr;

	Player::Player()
	{

	}

	Player::~Player()
	{

	}

	void Player::Initialize()
	{
		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mRigidBody = AddComponent<RigidBody>();
		curScene = SceneManager::GetActiveScene();

		hp = 5;
		atk = 1;

		deathFlag = false;
		invincibilityFlag = false;

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

		mAnimator->Play(L"Knight_Idleright", true);
		
		mCollider->SetName(L"PlayerCollider");
		mCollider->SetCenter(Vector2(-30.0f, -120.0f));
		mCollider->SetSize(Vector2(60.0f, 120.0f));

		mRigidBody->SetMass(0.01f);
		mRigidBody->SetGravity(Vector2(0.0f, 2000.0f));
		mState = ePlayerState::Idle;

		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		curScene = SceneManager::GetActiveScene();
		tr = GetComponent<Transform>();

		// HP�� 0���ϰ� �Ǹ� ����
		if (hp <= 0)
		{
			mState = ePlayerState::Death;
		}

		// 'L' ������ ������� �ٽ� ������ ����
		if (Input::GetKeyDown(eKeyCode::L))
		{
			if (invincibilityFlag == false)
				invincibilityFlag = true;
			else
				invincibilityFlag = false;
		}

		// �߸� ���·� ���ƿ��� ��� ���º��� �ʱ�ȭ
		if (mState == ePlayerState::Idle)
		{
			//idleFlag = false;
			walkFlag = false;
			slashFlag = false;
			slashAltFlag = false;
			upSlashFlag = false;
			downSlashFlag = false;
			dashFlag = false;
			deathFlag = false;
			focusFlag = false;
			focusEndFlag = false;
			focusGetFlag = false;
			focusGetOnceFlag = false;
			castFireballFlag = false;
			jumpFlag = false;
			doubleJumpFlag = false;
			fallFlag = false;
			//invincibilityFlag = false;

			mTime = 0.0f;
		}

		// ���� ���°� Ư�� ���°� �ƴϰ� onGround = true �� �ƴ� ��� fall ���·� 
		if (mRigidBody->GetGround() == false)
		{
			if ((mState != ePlayerState::Dash) && (mState != ePlayerState::Jump) 
				&& (mState != ePlayerState::DoubleJump) && (mState != ePlayerState::Recoil)
				&& (mState != ePlayerState::Slash) && (mState != ePlayerState::SlashAlt)
				&& (mState != ePlayerState::UpSlash) && (mState != ePlayerState::CastFireball)
				&& (mState != ePlayerState::DownSlash))
			{
				mState = ePlayerState::Fall;
				idleFlag = false;
			}
		}

		if (mRigidBody->GetGround() == true && idleFlag == false)
		{
			//mState = ePlayerState::Idle;
		}

		// �¿��̵� ���߸� rigidbody �ӵ� 0����
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
		eLayerType otherType = other->GetOwner()->GetType();	// �÷��̾�� �浹�� ��ü�� Ÿ��
		if (mState != ePlayerState::Death)
		{
			switch (otherType)
			{
			case eLayerType::Monster:
				if (!invincibilityFlag)
				{
					invincibilityFlag = true;

					mState = ePlayerState::Recoil;
					hp -= 1;

					if (mDirection == eDirection::Left)
					{
						mAnimator->Play(L"Knight_Recoilleft", true);
					}

					else if (mDirection == eDirection::Right)
					{
						mAnimator->Play(L"Knight_Recoilright", true);
					}
				}
				break;

			// �浹�� ��ü�� ���� ��� idle
			case eLayerType::Ground:
				mState = ePlayerState::Idle;
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"Knight_Idleleft", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"Knight_Idleright", true);

				mRigidBody->SetGround(true);

				break;
			}

			// ���Ϳ� ���˽� recoil state
			if (otherType == eLayerType::Monster && invincibilityFlag == false)
			{
				invincibilityFlag = true;

				mState = ePlayerState::Recoil;
				hp -= 1;

				if (mDirection == eDirection::Left)
				{
					mAnimator->Play(L"Knight_Recoilleft", true);
				}

				else if (mDirection == eDirection::Right)
				{
					mAnimator->Play(L"Knight_Recoilright", true);
				}

				return;
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
		}
		
		// �¿� �̵�Ű �Է½� Walk ���·� ����
		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Walk;
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Walkleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Walkright", true);
			idleFlag = false;

			return;
		}

		// Z �Է½� ����
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = ePlayerState::Jump;
			idleFlag = false;
			return;
		}

		// ���Ű �Է½� dash ���·� ����
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			idleFlag = false;
			return;
		}

		// up + ����Ű ������ UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			idleFlag = false;
			return;
		}

		// ���� �Է½� Slash ���� ����
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			idleFlag = false;
			return;
		}

		// S �Է½� ���Ÿ� ����
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::CastFireball;
			idleFlag = false;
			return;
		}

		// A �Է½� ü��ȸ��
		if (Input::GetKeyDown(eKeyCode::A))
		{
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

		// �̵�Ű���� ���� �� ��� Idle���·� ����
		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Idle;

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Idleright", true);

			return;
		}

		// ���Ű �Է½� dash ���·� ����
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			return;
		}

		// Z �Է½� ����
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = ePlayerState::Jump;
			return;
		}

		// up + ����Ű ������ UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			return;
		}

		// ���� �Է½� Slash ���� ����
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			return;
		}

		// S �Է½� ���Ÿ� ����
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::CastFireball;
			return;
		}

		// A �Է½� ü��ȸ��
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState = ePlayerState::Focus;
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
				//object::Instantiate<SlashEffectLeft>(tr->GetPos() + Vector2(-60.0f, 0.0f), eLayerType::Effect);
				slashFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Slashright", true);
				//object::Instantiate<SlashEffectRight>(tr->GetPos() + Vector2(60.0f, 0.0f), eLayerType::Effect);
				slashFlag = true;
				break;

			default:
				break;
			}
			object::Instantiate<SlashEffect>(eLayerType::Effect);
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.25f)
		{
			// up + ����Ű ������ UpSlash
			if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
			{
				mState = ePlayerState::UpSlash;
				mTime = 0.0f;
				slashFlag = false;
				return;
			}

			// slash ���¿��� �ѹ� �� ���ݽ� slashAlt ���� ����
			if (Input::GetKeyDown(eKeyCode::X))
			{
				mState = ePlayerState::SlashAlt;
				mTime = 0.0f;
				slashFlag = false;
				return;
			}
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
				//object::Instantiate<SlashAltEffectLeft>(tr->GetPos() + Vector2(-40.0f, -10.0f), eLayerType::Effect);
				slashAltFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_SlashAltright", true);
				//object::Instantiate<SlashAltEffectRight>(tr->GetPos() + Vector2(40.0f, -10.0f), eLayerType::Effect);
				slashAltFlag = true;
				break;

			default:
				break;
			}
			object::Instantiate<SlashAltEffect>(eLayerType::Effect);
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.25f)
		{
			// up + ����Ű ������ UpSlash
			if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
			{
				mState = ePlayerState::UpSlash;
				mTime = 0.0f;
				slashAltFlag = false;
				return;
			}

			// slashAlt ���¿��� �ѹ� �� ���ݽ� slash ���·� ����
			if (Input::GetKeyDown(eKeyCode::X))
			{
				mState = ePlayerState::Slash;
				mTime = 0.0f;
				slashAltFlag = false;
				return;
			}
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

	void Player::upSlash()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (upSlashFlag == false)
		{
			mAnimator->Play(L"Knight_UpSlashneutral", true);
			object::Instantiate<UpSlashEffect>(eLayerType::Effect);
			upSlashFlag = true;
		}

		Vector2 pos = tr->GetPos();
		if (Input::GetKey(eKeyCode::LEFT))
			pos.x -= 300.0f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::RIGHT))
			pos.x += 300.0f * Time::DeltaTime();
		tr->SetPos(pos);
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
			object::Instantiate<DownSlashEffect>(eLayerType::Effect);
			downSlashFlag = true;
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
		}

		// �뽬 �߿��� �߷� ���� x
		/*
		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
			pos.x -= 800.0f * Time::DeltaTime();
		else if (mDirection == eDirection::Right)
			pos.x += 800.0f * Time::DeltaTime();
		tr->SetPos(pos);
		*/
		mRigidBody->SetVelocity((Vector2::Zero));
		Vector2 velocity = mRigidBody->GetVelocity();
		if (mDirection == eDirection::Left)
			velocity.x = -800.0f;
		if (mDirection == eDirection::Right)
			velocity.x = 800.0f;
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

			// ���� �������ӵ� ����
			Vector2 velocity = mRigidBody->GetVelocity();
			velocity.y -= 900.0f;
			mRigidBody->SetVelocity(velocity);
			mRigidBody->SetGround(false);
		}

		// �ѹ� �� ����Ű �Է½� ��������
		if (Input::GetKeyDown(eKeyCode::Z) && doubleJumpFlag == false)
		{
			mState = ePlayerState::DoubleJump;
			jumpFlag = false;
			return;
		}

		// ���Ű �Է½� dash ���·� ����
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			jumpFlag = false;
			return;
		}

		// up + ����Ű ������ UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			jumpFlag = false;
			return;
		}

		// down + ���� �Է½� DownSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownSlash;
			jumpFlag = false;
			return;
		}

		// ���� �Է½� Slash ���� ����
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			jumpFlag = false;
			return;
		}

		// S �Է½� ���Ÿ� ����
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::CastFireball;
			jumpFlag = false;
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

			// �߷� �ʱ�ȭ ����� ��
			// ���� �������ӵ� ����
			Vector2 velocity = mRigidBody->GetVelocity();
			velocity.y = -800.0f;
			mRigidBody->SetVelocity(velocity);
			mRigidBody->SetGround(false);
		}

		// ���Ű �Է½� dash ���·� ����
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			return;
		}

		// up + ����Ű ������ UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			return;
		}

		// down + ���� �Է½� DownSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownSlash;
			return;
		}

		// ���� �Է½� Slash ���� ����
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			return;
		}

		// S �Է½� ���Ÿ� ����
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::CastFireball;
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

	void Player::fall()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (fallFlag == false)
		{
			mRigidBody->SetVelocity(Vector2::Zero);

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

			//���� ���� �÷��� �ʱ�ȭ
			dashFlag = false;
			castFireballFlag = false;
			slashFlag = false;
			slashAltFlag = false;
			upSlashFlag = false;
			downSlashFlag = false;
		}

		// �ѹ� �� ����Ű �Է½� ��������
		if (Input::GetKeyDown(eKeyCode::Z) && doubleJumpFlag == false)
		{
			mState = ePlayerState::DoubleJump;
			fallFlag = false;
			return;
		}

		// ���Ű �Է½� dash ���·� ����
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = ePlayerState::Dash;
			fallFlag = false;
			return;
		}

		// up + ����Ű ������ UpSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpSlash;
			fallFlag = false;
			return;
		}

		// down + ���� �Է½� DownSlash
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownSlash;
			fallFlag = false;
			return;
		}

		// ���� �Է½� Slash ���� ����
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			fallFlag = false;
			return;
		}

		// S �Է½� ���Ÿ� ����
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::CastFireball;
			fallFlag = false;
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

	void Player::castFireball()
	{
		if (castFireballFlag == false)
		{
			object::Instantiate<FireballCastEffect>(tr->GetPos(), eLayerType::BackEffect);
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_FireballCastleft", false);
				object::Instantiate<FireballEffectLeft>(tr->GetPos(), eLayerType::Effect);
				//object::Instantiate<FireballCastEffectLeft>(tr->GetPos(), eLayerType::BackEffect);
				castFireballFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_FireballCastright", false);
				object::Instantiate<FireballEffectRight>(tr->GetPos(), eLayerType::Effect);
				//object::Instantiate<FireballCastEffectRight>(tr->GetPos(), eLayerType::BackEffect);
				castFireballFlag = true;
				break;

			default:
				break;
			}
		}

		// �ֹ����� �߿��� �߷� ���� x
		/*
		mRigidBody->SetVelocity((Vector2::Zero));
		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
			pos.x += 30.0f * Time::DeltaTime();
		else if (mDirection == eDirection::Right)
			pos.x -= 30.0f * Time::DeltaTime();
		tr->SetPos(pos);
		*/
		mRigidBody->SetVelocity((Vector2::Zero));
		Vector2 velocity = mRigidBody->GetVelocity();
		if (mDirection == eDirection::Left)
			velocity.x = 30.0f;
		if (mDirection == eDirection::Right)
			velocity.x = -30.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::recoil()
	{
		/*
		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
			pos.x += 100.0f * Time::DeltaTime();
		else if (mDirection == eDirection::Right)
			pos.x -= 100.0f * Time::DeltaTime();
		tr->SetPos(pos);
		*/
		mRigidBody->SetVelocity((Vector2::Zero));
		Vector2 velocity = mRigidBody->GetVelocity();
		if (mDirection == eDirection::Left)
			velocity.x = -50.0f;
		if (mDirection == eDirection::Right)
			velocity.x = 50.0f;
		mRigidBody->SetVelocity(velocity);
	}

	void Player::death()
	{
		if (deathFlag == false)
		{
			mAnimator->Play(L"Knight_Deathneutral", false);
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
		}

		// ȸ��Ű���� �� ���� ȸ������
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusFlag = false;
			mTime = 0.0f;
			return;
		}

		// 1�� �̻� ȸ����� ���� ������
		mTime += Time::DeltaTime();
		if (mTime >= 1)
		{
			mState = ePlayerState::FocusGet;
			focusFlag = false;
			mTime = 0.0f;
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
		}

		// ȸ��Ű���� �� ���� ȸ������
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusGetFlag = false;
			mTime = 0.0f;
			return;
		}

		// 1�� �̻� ȸ����� ���� ������
		mTime += Time::DeltaTime();
		if (mTime >= 1)
		{
			mState = ePlayerState::FocusGet;
			focusGetFlag = false;
			mTime = 0.0f;
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

		// ȸ��Ű���� �� ���� ȸ������
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusGetOnceFlag = false;
			mTime = 0.0f;
			return;
		}

		// 1�� �̻� ȸ����� ���� ������
		mTime += Time::DeltaTime();
		if (mTime >= 1)
		{
			mState = ePlayerState::FocusGetOnce;
			focusGetOnceFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void Player::slashEndEvent()
	{
		// ����, ������ ��� ����
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
		// ����, ������ ��� ����
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
		// ����, ������ ��� ����
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
		// ����, ������ ��� ����
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
		mState = ePlayerState::Idle;

		// ����, ������ ��� ����
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

	void Player::dashEndEvent()
	{
		// �뽬 ������ �뽬 ���� �����ϵ���
		dashFlag = false;

		// �뽬 ������ �� ����, ������ ��� ����
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
		object::Destroy(this);

		object::Instantiate<PlayerSkull>(tr->GetPos(), eLayerType::Player);
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
		// ȸ��Ű�� ��� �������� ��� �̾ ȸ��
		if (Input::GetKey(eKeyCode::A))
		{
			mState = ePlayerState::FocusGetOnce;
			focusGetFlag = false;
			return;
		}

		// �ƴ� ��� ȸ������ ������� 
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
		// ����, ������ ��� ����
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
}
