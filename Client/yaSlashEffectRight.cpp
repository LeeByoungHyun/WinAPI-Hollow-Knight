#include "yaSlashEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"

namespace ya
{
	SlashEffectRight::SlashEffectRight()
	{

	}

	SlashEffectRight::~SlashEffectRight()
	{

	}

	void SlashEffectRight::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashEffect\\right", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"Knight_SlashEffectright") = std::bind(&SlashEffectRight::slashEffectRightComplateEvent, this);

		mAnimator->Play(L"Knight_SlashEffectright", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-50.0f, -100.0f));
		mCollider->SetSize(Vector2(120.0f, 90.0f));

		GameObject::Initialize();
	}

	void SlashEffectRight::Update()
	{
		GameObject::Update();
	}

	void SlashEffectRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SlashEffectRight::Release()
	{
		GameObject::Release();

	}

	void SlashEffectRight::OnCollisionEnter(Collider* other)
	{
		CollisionObj = other->GetOwner();
	}

	void SlashEffectRight::OnCollisionStay(Collider* other)
	{
	}

	void SlashEffectRight::OnCollisionExit(Collider* other)
	{
	}

	void SlashEffectRight::slashEffectRightComplateEvent()
	{

		object::Destroy(this);
	}
}
