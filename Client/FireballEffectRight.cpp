#include "FireballEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"

namespace ya
{
	FireballEffectRight::FireballEffectRight()
	{
		mAnimator = AddComponent<Animator>();
	}

	FireballEffectRight::~FireballEffectRight()
	{

	}

	void FireballEffectRight::Initialize()
	{
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballEffect\\right", Vector2::Zero, 0.05f);
		mAnimator->GetCompleteEvent(L"Knight_FireballEffectright") = std::bind(&FireballEffectRight::fireballEffectRightEndEvent, this);
		mAnimator->Play(L"Knight_FireballEffectright", true);

		GameObject::Initialize();
	}

	void FireballEffectRight::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 2000.0f * Time::DeltaTime();
		tr->SetPos(pos);

		GameObject::Update();
	}

	void FireballEffectRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FireballEffectRight::Release()
	{
		GameObject::Release();
	}

	void FireballEffectRight::fireballEffectRightEndEvent()
	{
		object::Destroy(this);
	}
}