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
#include "mySlashEffectLeft.h"
#include "yaSlashEffectRight.h"
#include "yaSlashAltEffectLeft.h"
#include "yaSlashAltEffectRight.h"
#include "yaUpSlashEffect.h"
#include "yaDashEffectLeft.h"
#include "yaDashEffectRight.h"
#include "FireballEffectLeft.h"
#include "FireballEffectRight.h"

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
		tr = GetComponent<Transform>();
		tr->SetName(L"PlayerTransform");

		hp = 5;
		atk = 1;

		deathFlag = false;
		invincibilityFlag = false;

		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Idle\\right", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Walk\\right", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Dash\\left", Vector2::Zero, 0.025f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Dash\\right", Vector2::Zero, 0.025f);

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_Slash\\right", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAlt\\right", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_UpSlash\\neutral", Vector2::Zero, 0.05f);

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

		mAnimator->GetCompleteEvent(L"Knight_Slashleft") = std::bind(&Player::slashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_Slashright") = std::bind(&Player::slashEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltleft") = std::bind(&Player::slashAltEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltright") = std::bind(&Player::slashAltEndEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_UpSlashneutral") = std::bind(&Player::upSlashEndEvent, this);

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

		mAnimator->Play(L"Knight_Idleright", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetName(L"PlayerCollider");
		mCollider->SetCenter(Vector2(-30.0f, -120.0f));
		mCollider->SetSize(Vector2(60.0f, 120.0f));

		mState = ePlayerState::Idle;

		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		curScene = SceneManager::GetActiveScene();
		tr = GetComponent<Transform>();

		// HP가 0이하가 되면 죽음
		if (hp <= 0 && deathFlag == false)
		{
			mState = ePlayerState::Death;
			mAnimator->Play(L"Knight_Deathneutral", false);
			deathFlag = true;
		}

		// 중립 상태로 돌아오면 모든 상태변수 초기화
		if (mState == ePlayerState::Idle)
		{
			walkFlag = false;
			slashFlag = false;
			slashAltFlag = false;
			upSlashFlag = false;
			dashFlag = false;
			deathFlag = false;
			invincibilityFlag = false;
			focusFlag = false;
			focusEndFlag = false;
			focusGetFlag = false;
			focusGetOnceFlag = false;
			castFireballFlag = false;

			mTime = 0.0f;
		}

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
		if (mState != ePlayerState::Death)
		{
			// 몬스터 콜라이더와 접촉시 피격 애니메이션
			if (other->GetOwner()->GetType() == eLayerType::Monster && invincibilityFlag == false)
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

		// 좌우 이동키 입력시 Walk 상태로 변경
		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Walk;
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Knight_Walkleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Knight_Walkright", true);
			return;
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

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			return;
		}

		// S 입력시 원거리 공격
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::CastFireball;
			return;
		}

		// A 입력시 체력회복
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState = ePlayerState::Focus;
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

			return;
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

		// 공격 입력시 Slash 상태 변경
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Slash;
			return;
		}

		// A 입력시 체력회복
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState = ePlayerState::Focus;
			return;
		}

		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::LEFT))
			pos.x -= 200.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::RIGHT))
			pos.x += 200.0f * Time::DeltaTime();

		tr->SetPos(pos);
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
				object::Instantiate<SlashEffectLeft>(tr->GetPos() + Vector2(-60.0f, 0.0f), eLayerType::Effect);
				slashFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Slashright", true);
				object::Instantiate<SlashEffectRight>(tr->GetPos() + Vector2(60.0f, 0.0f), eLayerType::Effect);
				slashFlag = true;
				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.3f)
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
				object::Instantiate<SlashAltEffectLeft>(tr->GetPos() + Vector2(-40.0f, -10.0f), eLayerType::Effect);
				slashAltFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_SlashAltright", true);
				object::Instantiate<SlashAltEffectRight>(tr->GetPos() + Vector2(40.0f, -10.0f), eLayerType::Effect);
				slashAltFlag = true;
				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.3f)
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
			object::Instantiate<UpSlashEffect>(tr->GetPos() + Vector2(0.0f, -0.0f), eLayerType::Effect);
			upSlashFlag = true;
		}
	}

	void Player::dash()
	{
		if (dashFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_Dashleft", false);
				object::Instantiate<DashEffectLeft>(tr->GetPos() + Vector2(130.0f, 30.0f), eLayerType::Effect);
				dashFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_Dashright", false);
				object::Instantiate<DashEffectRight>(tr->GetPos() + Vector2(-130.0f, 30.0f), eLayerType::Effect);
				dashFlag = true;
				break;

			default:
				break;
			}
		}

		Vector2 pos = tr->GetPos();

		if (mDirection == eDirection::Left)
			pos.x -= 800.0f * Time::DeltaTime();

		else if (mDirection == eDirection::Right)
			pos.x += 800.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}

	void Player::jump()
	{

	}

	void Player::fall()
	{

	}

	void Player::castFireball()
	{
		if (castFireballFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Knight_FireballCastleft", false);
				object::Instantiate<FireballEffectLeft>(tr->GetPos(), eLayerType::Effect);
				castFireballFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Knight_FireballCastright", false);
				object::Instantiate<FireballEffectRight>(tr->GetPos(), eLayerType::Effect);
				castFireballFlag = true;
				break;

			default:
				break;
			}
		}

		Vector2 pos = tr->GetPos();

		if (mDirection == eDirection::Left)
			pos.x += 30.0f * Time::DeltaTime();

		else if (mDirection == eDirection::Right)
			pos.x -= 30.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}

	void Player::recoil()
	{
		Vector2 pos = tr->GetPos();

		if (mDirection == eDirection::Left)
			pos.x += 100.0f * Time::DeltaTime();

		else if (mDirection == eDirection::Right)
			pos.x -= 100.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}

	void Player::death()
	{
		
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
		}

		// 회복키에서 손 때면 회복종료
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusFlag = false;
			return;
		}

		// 1초 이상 회복모션 유지 성공시
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
				mAnimator->Play(L"Knight_FocusEndleft", false);
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
		}

		// 회복키에서 손 때면 회복종료
		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::FocusEnd;
			focusGetOnceFlag = false;
			return;
		}

		// 1초 이상 회복모션 유지 성공시
		mTime += Time::DeltaTime();
		if (mTime >= 1)
		{
			mState = ePlayerState::FocusGet;
			focusGetOnceFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void Player::slashEndEvent()
	{
		mState = ePlayerState::Idle;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::slashAltEndEvent()
	{
		mState = ePlayerState::Idle;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::upSlashEndEvent()
	{
		mState = ePlayerState::Idle;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::recoilEndEvent()
	{
		mState = ePlayerState::Idle;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);

		invincibilityFlag = false;
	}

	void Player::dashEndEvent()
	{
		mState = ePlayerState::Idle;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}

	void Player::deathEndEvent()
	{
		object::Destroy(this);
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
		mState = ePlayerState::Idle;

		if (mDirection == eDirection::Left)
			mAnimator->Play(L"Knight_Idleleft", true);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"Knight_Idleright", true);
	}
}
