#include "FalseAttackWave.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaRigidBody.h"

#include "FalseKnight.h"
#include "yaPlayer.h"
#include "Wave01.h"
#include "Wave02.h"
#include "Wave03.h"

namespace ya
{
	FalseAttackWave::FalseAttackWave()
	{

	}

	FalseAttackWave::~FalseAttackWave()
	{

	}

	void FalseAttackWave::Initialize()
	{
		tr = AddComponent<Transform>();
		mState = eFalseAttackWaveState::Disable;

		GameObject::Initialize();
	}

	void FalseAttackWave::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::FalseAttackWave::eFalseAttackWaveState::Disable:
			disable();
			break;

		case ya::FalseAttackWave::eFalseAttackWaveState::Active:
			active();
			break;

		default:
			break;
		}
	}

	void FalseAttackWave::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseAttackWave::Release()
	{
		GameObject::Release();
	}

	void FalseAttackWave::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void FalseAttackWave::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void FalseAttackWave::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void FalseAttackWave::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			//mCollider->SetSize(Vector2::Zero);
			//mCollider->SetActive(false);
			mTime = 0.0f;
			wave01Flag = false;
			//this->SetState(eState::Pause);
		}
	}

	void FalseAttackWave::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;

			// Hornet위치에 생성
			Vector2 pos = FalseKnight::GetInstance()->GetComponent<Transform>()->GetPos();
			//pos.y -= 40.0f;
			tr->SetPos(pos);

		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.1f && wave01Flag == false)
		{
			wave01 = object::Instantiate<Wave01>(eLayerType::Monster);
			wave01->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave01Flag = true;

			mState = eFalseAttackWaveState::Disable;
		}
	}
}