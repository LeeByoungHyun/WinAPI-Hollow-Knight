#include "CounterAttackCollider.h"
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
	CounterAttackCollider::CounterAttackCollider()
	{
		
	}

	CounterAttackCollider::~CounterAttackCollider()
	{

	}

	void CounterAttackCollider::Initialize()
	{
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mState = eCounterAttackColliderState::Disable;

		GameObject::Initialize();
	}

	void CounterAttackCollider::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::CounterAttackCollider::eCounterAttackColliderState::Disable:
			disable();
			break;

		case ya::CounterAttackCollider::eCounterAttackColliderState::Active:
			active();
			break;

		default:
			break;
		}

	}

	void CounterAttackCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void CounterAttackCollider::Release()
	{
		GameObject::Release();
	}

	void CounterAttackCollider::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void CounterAttackCollider::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void CounterAttackCollider::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void CounterAttackCollider::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			mCollider->SetSize(Vector2::Zero);
			mCollider->SetActive(false);
			this->SetState(eState::Pause);
		}
	}

	void CounterAttackCollider::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;

			// Hornet위치에 생성
			Vector2 pos = Hornet::GetInstance()->GetComponent<Transform>()->GetPos();
			pos.y -= 40.0f;
			tr->SetPos(pos);

			
			mCollider->SetActive(true);

			if (mDirection == eDirection::Left)
			{
				mCollider->SetSize(Vector2(540.0f, 325.0f));
				mCollider->SetCenter(Vector2(-270.0f, -295.0f));
			}
			else
			{
				mCollider->SetSize(Vector2(540.0f, 325.0f));
				mCollider->SetCenter(Vector2(-270.0f, -295.0f));
			}
		}

		if (Hornet::GetInstance()->GetHornetState()!=Hornet::eHornetState::CounterAttack)
		{
			mState = eCounterAttackColliderState::Disable;
		}
	}
}