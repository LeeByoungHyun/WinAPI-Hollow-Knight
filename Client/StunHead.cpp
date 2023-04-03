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
		mRigidbody = AddComponent<RigidBody>();
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
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\left", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\right", Vector2::Zero, 0.033f);

		mState = eStunHeadState::Idle;
	}

	void StunHead::Update()
	{
		switch (mState)
		{
		case ya::StunHead::eStunHeadState::Idle:
			idle();
			break;

		case ya::StunHead::eStunHeadState::Hit:
			hit();
			break;

		default:
			break;
		}
	}

	void StunHead::Render(HDC hdc)
	{
		
	}

	void StunHead::Release()
	{

	}

	void StunHead::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();	// 플레이어와 충돌한 객체의 타입
		int hp = mFalseKnight->GetTrueHP();
		switch (otherType)
		{
		// 플레이어의 공격일 경우
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
				mAnimator->Play(L"False Knight_Head(Idle)left", true);
				idleFlag = true;
				break;

			case eDirection::Right:	// right
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
				mAnimator->Play(L"False Knight_Head(Hit)left", true);
				hitFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"False Knight_Head(Hit)right", true);
				hitFlag = true;
				break;

			default:
				break;
			}

			idleFlag = false;
		}
	}
}