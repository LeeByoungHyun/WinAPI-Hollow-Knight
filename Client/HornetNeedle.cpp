#include "HornetNeedle.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaRigidBody.h"

#include "Hornet.h"
#include "yaPlayer.h"

namespace ya
{
	Vector2 HornetNeedlePlayerPos;
	Vector2 HornetNeedlePlayerDir;

	HornetNeedle::HornetNeedle()
	{
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();
	}

	HornetNeedle::~HornetNeedle()
	{

	}

	void HornetNeedle::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Needle)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Needle)\\right", Vector2::Zero, 0.1f);


		GameObject::Initialize();
	}

	void HornetNeedle::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::HornetNeedle::eHornetNeedleState::Disable:
			disable();
			break;

		case ya::HornetNeedle::eHornetNeedleState::Active:
			active();
			break;

		default:
			break;
		}

	}

	void HornetNeedle::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HornetNeedle::Release()
	{
		GameObject::Release();
	}

	void HornetNeedle::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		eLayerType otherType = other->GetOwner()->GetType();	// 충돌한 객체의 타입
		switch (otherType)
		{
			// hornet
		case eLayerType::Monster:
			if (NEEDLESPEED <= 0.0f)
			{
				mState = eHornetNeedleState::Disable;
			}
			break;
		}
	}

	void HornetNeedle::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void HornetNeedle::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void HornetNeedle::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			mCollider->SetSize(Vector2::Zero);
			mCollider->SetActive(false);
			NEEDLESPEED = 1500.0f;
			this->SetState(eState::Pause);
		}
	}

	void HornetNeedle::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;

			// Hornet위치에 생성
			Vector2 pos = Hornet::GetInstance()->GetComponent<Transform>()->GetPos();
			pos.y -= 40.0f;
			tr->SetPos(pos);

			mCollider->SetSize(Vector2(260.0f, 20.0f));
			mCollider->SetCenter(Vector2(-130.0f, -20.0f));
			mCollider->SetActive(true);

			if (mDirection == eDirection::Left)
			{
				mAnimator->Play(L"Hornet_Throw(Needle)left", false);
			}
			else
			{
				mAnimator->Play(L"Hornet_Throw(Needle)right", false);
			}
		}

		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
		{
			pos.x -= NEEDLESPEED * Time::DeltaTime();
		}
		else
		{
			pos.x += NEEDLESPEED * Time::DeltaTime();
		}
		NEEDLESPEED -= DECELERATION * Time::DeltaTime();
		tr->SetPos(pos);
	}
}