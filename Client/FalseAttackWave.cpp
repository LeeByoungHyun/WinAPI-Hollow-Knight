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
	const float FALSEWAVETIME = 0.033f;

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

		wave01 = object::Instantiate<Wave01>(eLayerType::Monster);
		wave02 = object::Instantiate<Wave01>(eLayerType::Monster);
		wave03 = object::Instantiate<Wave02>(eLayerType::Monster);
		wave04 = object::Instantiate<Wave02>(eLayerType::Monster);
		wave05 = object::Instantiate<Wave02>(eLayerType::Monster);
		wave06 = object::Instantiate<Wave03>(eLayerType::Monster);
		wave07 = object::Instantiate<Wave03>(eLayerType::Monster);
		wave08 = object::Instantiate<Wave03>(eLayerType::Monster);
		wave09 = object::Instantiate<Wave02>(eLayerType::Monster);
		wave10 = object::Instantiate<Wave02>(eLayerType::Monster);
		wave11 = object::Instantiate<Wave01>(eLayerType::Monster);

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
			mTime = 0.0f;
			wave01Flag = false;
			wave02Flag = false;
			wave03Flag = false;
			wave04Flag = false;
			wave05Flag = false;
			wave06Flag = false;
			wave07Flag = false;
			wave08Flag = false;
			wave09Flag = false;
			wave10Flag = false;
			wave11Flag = false;
		}
	}

	void FalseAttackWave::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;

			Vector2 pos = FalseKnight::GetInstance()->GetComponent<Transform>()->GetPos();
			tr->SetPos(pos);
		}

		mTime += Time::DeltaTime();
		if (mTime >= FALSEWAVETIME * 0.0f && wave01Flag == false)
		{
			wave01->SetWaveState(Wave01::eWave01State::Active);
			wave01->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave01->SetPos(tr->GetPos());
			wave01Flag = true;

		}
		if (mTime >= FALSEWAVETIME * 1.0f && wave02Flag == false)
		{
			wave02->SetWaveState(Wave01::eWave01State::Active);
			wave02->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave02->SetPos(tr->GetPos());
			wave02Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 2.0f && wave03Flag == false)
		{
			wave03->SetWaveState(Wave02::eWave02State::Active);
			wave03->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave03->SetPos(tr->GetPos());
			wave03Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 3.0f && wave04Flag == false)
		{
			wave04->SetWaveState(Wave02::eWave02State::Active);
			wave04->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave04->SetPos(tr->GetPos());
			wave04Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 4.0f && wave05Flag == false)
		{
			wave05->SetWaveState(Wave02::eWave02State::Active);
			wave05->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave05->SetPos(tr->GetPos());
			wave05Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 5.0f && wave06Flag == false)
		{
			wave06->SetWaveState(Wave03::eWave03State::Active);
			wave06->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave06->SetPos(tr->GetPos());
			wave06Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 6.0f && wave07Flag == false)
		{
			wave07->SetWaveState(Wave03::eWave03State::Active);
			wave07->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave07->SetPos(tr->GetPos());
			wave07Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 7.0f && wave08Flag == false)
		{
			wave08->SetWaveState(Wave03::eWave03State::Active);
			wave08->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave08->SetPos(tr->GetPos());
			wave08Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 8.0f && wave09Flag == false)
		{
			wave09->SetWaveState(Wave02::eWave02State::Active);
			wave09->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave09->SetPos(tr->GetPos());
			wave09Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 9.0f && wave10Flag == false)
		{
			wave10->SetWaveState(Wave02::eWave02State::Active);
			wave10->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave10->SetPos(tr->GetPos());
			wave10Flag = true;
		}
		if (mTime >= FALSEWAVETIME * 10.0f && wave11Flag == false)
		{
			wave11->SetWaveState(Wave01::eWave01State::Active);
			wave11->GetComponent<Transform>()->SetPos(tr->GetPos());
			wave11->SetPos(tr->GetPos());
			wave11Flag = true;

			mState = eFalseAttackWaveState::Disable;
		}
	}
}