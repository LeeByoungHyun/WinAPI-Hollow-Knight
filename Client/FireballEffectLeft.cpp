#include "FireballEffectLeft.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "FireballHitEffect.h"

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
		tr = AddComponent<Transform>();

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-70.0f, -100.0f));
		mCollider->SetSize(Vector2(120.0f, 90.0f));

		GameObject::Initialize();
	}

	void FireballEffectLeft::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x -= 3000.0f * Time::DeltaTime();
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

	void FireballEffectLeft::OnCollisionEnter(Collider* other)
	{
		if ((other->GetOwner()->GetType() == eLayerType::FalseKnight || 
			other->GetOwner()->GetType() == eLayerType::Hornet ||
			other->GetOwner()->GetType() == eLayerType::Monster) && hitFlag == false)
		{
			
			object::Instantiate<FireballHitEffect>(tr->GetPos(), eLayerType::Effect);

			hitFlag = true;
		}
	}

	void FireballEffectLeft::OnCollisionStay(Collider* other)
	{

	}

	void FireballEffectLeft::OnCollisionExit(Collider* other)
	{

	}

	void FireballEffectLeft::fireballEffectLeftEndEvent()
	{
		object::Destroy(this);
	}
}