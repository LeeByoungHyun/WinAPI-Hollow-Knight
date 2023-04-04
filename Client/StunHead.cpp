#include "StunHead.h"
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

#include "yaPlayer.h"
#include "FalseKnight.h"

namespace ya
{
	StunHead::StunHead()
	{
		//mRigidbody = AddComponent<RigidBody>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();
		mFalseKnight = FalseKnight::GetInstance();
		mPlayer = Player::GetInstance();
	}

	StunHead::~StunHead()
	{

	}

	void StunHead::Initialize()
	{
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Idle)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Idle)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 1)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 1)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 2)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 2)\\right", Vector2::Zero, 0.1f);
		mAnimator->GetCompleteEvent(L"False Knight_Head(Hit)left") = std::bind(&StunHead::hitCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Head(Hit)right") = std::bind(&StunHead::hitCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Death(Head 1)left") = std::bind(&StunHead::deathHead1CompleteEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Death(Head 1)right") = std::bind(&StunHead::deathHead1CompleteEvent, this);

		mState = eStunHeadState::Idle;

		GameObject::Initialize();
	}

	void StunHead::Update()
	{
		// 40 �̻��� ���ظ� ������ �����

		if (mFalseKnight->GetTrueHP() <= 0)
		{
			mState = eStunHeadState::Death;
		}
		else if(mFalseKnight->GetTrueHP() <= 160 - (mFalseKnight->GetStunCount() * 40))
		{
			object::Destroy(this);
		}

		switch (mState)
		{
		case ya::StunHead::eStunHeadState::Idle:
			idle();
			break;

		case ya::StunHead::eStunHeadState::Hit:
			hit();
			break;

		case ya::StunHead::eStunHeadState::Death:
			death();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void StunHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void StunHead::Release()
	{
		GameObject::Release();
	}

	void StunHead::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();	// �÷��̾�� �浹�� ��ü�� Ÿ��
		int hp = mFalseKnight->GetTrueHP();
		switch (otherType)
		{
		// �÷��̾��� ������ ���
		case eLayerType::NeilEffect:
			mState = eStunHeadState::Hit;
			hp -= mPlayer->GetNeilAtk();
			mFalseKnight->SetTrueHP(hp);
			break;

		case eLayerType::SpellEffect:
			mState = eStunHeadState::Hit;
			hp -= mPlayer->GetSpellAtk();
			mFalseKnight->SetTrueHP(hp);
			break;
		}
	}

	void StunHead::OnCollisionStay(Collider* other)
	{

	}

	void StunHead::OnCollisionExit(Collider* other)
	{

	}

	void StunHead::idle()
	{
		if (idleFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetSize(Vector2(120.0f, 120.0f));
				mCollider->SetCenter(Vector2(-60.0f, -120.0f));
				mAnimator->Play(L"False Knight_Head(Idle)left", true);
				idleFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetSize(Vector2(120.0f, 120.0f));
				mCollider->SetCenter(Vector2(-60.0f, -120.0f));
				mAnimator->Play(L"False Knight_Head(Idle)right", true);
				idleFlag = true;
				break;

			default:
				break;
			}

			hitFlag = false;
		}
	}

	void StunHead::hit()
	{
		if (hitFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"False Knight_Head(Hit)left", false);
				hitFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"False Knight_Head(Hit)right", false);
				hitFlag = true;
				break;

			default:
				break;
			}

			idleFlag = false;
		}
	}

	void StunHead::death()
	{
		mCollider->SetActive(false);
		mCollider->SetSize(Vector2(0.0f, 0.0f));
		if (deathFlag1 == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"False Knight_Head(Hit)left", true);
				deathFlag1 = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"False Knight_Head(Hit)right", true);
				deathFlag1 = true;
				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 3.0f && deathFlag2 == false)
		{
			deathFlag2 = true;
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"False Knight_Death(Head 1)left", false);
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"False Knight_Death(Head 1)right", false);
				break;

			default:
				break;
			}
		}

		if (mTime >= 3.0f && deathFlag3 == false)
		{
			Vector2 pos = tr->GetPos();
			switch (mDirection)
			{
			case eDirection::Left:	// left
				pos.x -= 200.0f * Time::DeltaTime();
				break;

			case eDirection::Right:	// right
				pos.x += 200.0f * Time::DeltaTime();
				break;

			default:
				break;
			}
			tr->SetPos(pos);
		}
	}

	void StunHead::hitCompleteEvent()
	{
		mState = eStunHeadState::Idle;
	}

	void StunHead::deathHead1CompleteEvent()
	{
		switch (mDirection)
		{
		case eDirection::Left:	// left
			mAnimator->Play(L"False Knight_Death(Head 2)left", false);
			break;

		case eDirection::Right:	// right
			mAnimator->Play(L"False Knight_Death(Head 2)right", false);
			break;

		default:
			break;
		}

		deathFlag3 = true;
	}







}