#include "MantisLordsProjectile.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaRigidBody.h"

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
		mCollider->SetCenter(Vector2(-150.0f, -100.0f));
		mCollider->SetSize(Vector2(300.0f, 100.0f));

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
			speed = 800.0f;	// �ʱ� ����ü �ӵ�

			Vector2 pos = tr->GetPos();
			pos.y -= 300.0f;	// ����ü ���� ��ġ ����
			tr->SetPos(pos);
		}

		// ���⿡�� ���������� �����̵��� �����ؾ� ��
		// �׽�Ʈ������ ���������� ���ư����� ����
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x += speed * Time::DeltaTime();
			speed -= 50.0f * Time::DeltaTime();	// ����ü ���� ��ġ
			pos.y += 10.2f * Time::DeltaTime();	// ����ü �ϰ� ��ġ

			tr->SetPos(pos);
		}
		else
		{
			Vector2 pos = tr->GetPos();
			pos.x -= speed * Time::DeltaTime();
			speed -= 50.0f * Time::DeltaTime();	// ����ü ���� ��ġ
			pos.y += 10.2f * Time::DeltaTime();	// ����ü �ϰ� ��ġ

			tr->SetPos(pos);
		}
		
		mTime += Time::DeltaTime();
		if (mTime >= 6.0f)
		{
			mTime = 0.0f;
			mState = eProjectileState::Disable;
		}
	}
}