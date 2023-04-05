#include "MantisLordsProjectile.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"

#include "MantisLord1.h"

namespace ya
{
	MantisLordsProjectile::MantisLordsProjectile()
	{
		tr = AddComponent<Transform>();
	}

	MantisLordsProjectile::~MantisLordsProjectile()
	{

	}

	void MantisLordsProjectile::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Air Projectile\\neutral", Vector2::Zero, 0.033f);
		mAnimator->Play(L"Mantis Lords_Air Projectileneutral", true);

		mCollider = AddComponent<Collider>();

		GameObject::Initialize();
	}

	void MantisLordsProjectile::Update()
	{
		switch (mState)
		{
		case ya::MantisLordsProjectile::eProjectileState::Disable:
			disable();
			break;

		case ya::MantisLordsProjectile::eProjectileState::Active:
			active();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void MantisLordsProjectile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MantisLordsProjectile::Release()
	{
		GameObject::Release();
	}

	void MantisLordsProjectile::OnCollisionEnter(Collider* other)
	{

	}

	void MantisLordsProjectile::OnCollisionStay(Collider* other)
	{

	}

	void MantisLordsProjectile::OnCollisionExit(Collider* other)
	{

	}

	void MantisLordsProjectile::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			this->SetState(eState::Pause);
		}
	}

	void MantisLordsProjectile::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;
			this->SetState(eState::Active);
		}

		// 여기에서 포물선으로 움직이도록 구현해야 함
		// 테스트용으로 일직선으로 날아가도록 구현
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 100.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 100.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		
		mTime += Time::DeltaTime();
		if (mTime >= 5.0f)
		{
			mTime = 0.0f;
			mState = eProjectileState::Disable;
		}
	}
}