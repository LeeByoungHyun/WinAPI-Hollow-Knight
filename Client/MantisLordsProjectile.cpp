#include "MantisLordsProjectile.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"

namespace ya
{
	MantisLordsProjectile::MantisLordsProjectile()
	{

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
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 100.0f * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime >= 5.0f)
			object::Destroy(this);

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
}