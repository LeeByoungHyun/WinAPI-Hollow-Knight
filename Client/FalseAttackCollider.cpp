#include "FalseAttackCollider.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaRigidBody.h"

#include "FalseKnight.h"
#include "yaPlayer.h"

namespace ya
{
	FalseAttackCollider::FalseAttackCollider()
	{

	}

	FalseAttackCollider::~FalseAttackCollider()
	{

	}

	void FalseAttackCollider::Initialize()
	{
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mState = eFalseAttackColliderState::Disable;

		GameObject::Initialize();
	}

	void FalseAttackCollider::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::FalseAttackCollider::eFalseAttackColliderState::Disable:
			disable();
			break;

		case ya::FalseAttackCollider::eFalseAttackColliderState::Active:
			active();
			break;

		default:
			break;
		}

	}

	void FalseAttackCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseAttackCollider::Release()
	{
		GameObject::Release();
	}

	void FalseAttackCollider::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void FalseAttackCollider::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void FalseAttackCollider::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void FalseAttackCollider::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;
			mTime = 0.0f;
			tr->SetPos(Vector2::Zero);
			mCollider->SetSize(Vector2::Zero);
			mCollider->SetActive(false);
			this->SetState(eState::Pause);
		}
	}

	void FalseAttackCollider::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;

			// Hornet위치에 생성
			Vector2 pos = FalseKnight::GetInstance()->GetComponent<Transform>()->GetPos();
			//pos.y -= 40.0f;
			tr->SetPos(pos);

			mCollider->SetActive(true);

			if (FalseKnight::GetInstance()->GetDirection() == FalseKnight::eDirection::Left)
			{
				mCollider->SetSize(Vector2(370.0f, 450.0f));
				mCollider->SetCenter(Vector2(-370.0f, -450.0f));
			}
			else
			{
				mCollider->SetSize(Vector2(370.0f, 450.0f));
				mCollider->SetCenter(Vector2(0.0f, -450.0f));
			}
		}
		mTime += Time::DeltaTime();
		if (mTime >= 0.1f)
		{
			mState = eFalseAttackColliderState::Disable;
			mTime = 0.0f;
		}
	}
}