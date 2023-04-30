#include "FireballEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "FireballHitEffect.h"

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
		tr = AddComponent<Transform>();

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-50.0f, -100.0f));
		mCollider->SetSize(Vector2(120.0f, 90.0f));

		GameObject::Initialize();
	}

	void FireballEffectRight::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 3000.0f * Time::DeltaTime();
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

	void FireballEffectRight::OnCollisionEnter(Collider* other)
	{
		if ((other->GetOwner()->GetType() == eLayerType::FalseKnight ||
			other->GetOwner()->GetType() == eLayerType::Hornet ||
			other->GetOwner()->GetType() == eLayerType::Monster) && hitFlag == false)
		{

			object::Instantiate<FireballHitEffect>(tr->GetPos(), eLayerType::Effect);

			hitFlag = true;
		}
	}

	void FireballEffectRight::OnCollisionStay(Collider* other)
	{

	}

	void FireballEffectRight::OnCollisionExit(Collider* other)
	{

	}

	void FireballEffectRight::fireballEffectRightEndEvent()
	{
		object::Destroy(this);
	}
}