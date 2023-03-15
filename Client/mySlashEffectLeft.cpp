#include "mySlashEffectLeft.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"

namespace ya
{
	SlashEffectLeft::SlashEffectLeft()
	{

	}

	SlashEffectLeft::~SlashEffectLeft()
	{

	}

	void SlashEffectLeft::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashEffect\\left", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"Knight_SlashEffectleft") = std::bind(&SlashEffectLeft::slashEffectLeftComplateEvent, this);

		mAnimator->Play(L"Knight_SlashEffectleft", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-70.0f, -100.0f));
		mCollider->SetSize(Vector2(120.0f, 90.0f));

		GameObject::Initialize();
	}

	void SlashEffectLeft::Update()
	{
		GameObject::Update();
	}

	void SlashEffectLeft::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SlashEffectLeft::Release()
	{
		GameObject::Release();

	}

	void SlashEffectLeft::OnCollisionEnter(Collider* other)
	{
		//other->GetOwner();

	}

	void SlashEffectLeft::OnCollisionStay(Collider* other)
	{
	}

	void SlashEffectLeft::OnCollisionExit(Collider* other)
	{
	}

	void SlashEffectLeft::slashEffectLeftComplateEvent()
	{
		object::Destroy(this);
	}
}
