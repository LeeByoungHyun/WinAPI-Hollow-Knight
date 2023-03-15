#include "FireballEffectLeft.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"

namespace ya
{
	FireballEffectLeft::FireballEffectLeft()
	{
		mAnimator = AddComponent<Animator>();
	}

	FireballEffectLeft::~FireballEffectLeft()
	{

	}

	void FireballEffectLeft::Initialize()
	{
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballEffect\\left", Vector2::Zero, 0.05f);
		mAnimator->GetCompleteEvent(L"Knight_FireballEffectleft") = std::bind(&FireballEffectLeft::fireballEffectLeftEndEvent, this);
		mAnimator->Play(L"Knight_FireballEffectleft", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-70.0f, -100.0f));
		mCollider->SetSize(Vector2(120.0f, 90.0f));

		GameObject::Initialize();
	}

	void FireballEffectLeft::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x -= 2000.0f * Time::DeltaTime();
		tr->SetPos(pos);

		GameObject::Update();
	}

	void FireballEffectLeft::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FireballEffectLeft::Release()
	{
		GameObject::Release();
	}

	void FireballEffectLeft::fireballEffectLeftEndEvent()
	{
		object::Destroy(this);
	}
}