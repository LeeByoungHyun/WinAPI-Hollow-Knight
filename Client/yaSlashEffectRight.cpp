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
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashEffect\\right", Vector2::Zero, 0.05f);

		mAnimator->GetCompleteEvent(L"Knight_SlashEffectright") = std::bind(&SlashEffectRight::slashEffectRightComplateEvent, this);

		mAnimator->Play(L"Knight_SlashEffectright", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-60.0f, -80.0f));
		mCollider->SetSize(Vector2(120.0f, 60.0f));

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

	void SlashEffectRight::slashEffectRightComplateEvent()
	{
		object::Destroy(this);
	}
}
