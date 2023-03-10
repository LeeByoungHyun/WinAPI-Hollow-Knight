#include "yaSlashAltEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"	

namespace ya
{
	SlashAltEffectRight::SlashAltEffectRight()
	{

	}

	SlashAltEffectRight::~SlashAltEffectRight()
	{

	}

	void SlashAltEffectRight::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAltEffect\\right", Vector2::Zero, 0.05f);

		mAnimator->GetCompleteEvent(L"Knight_SlashAltEffectright") = std::bind(&SlashAltEffectRight::slashAltEffectRightComplateEvent, this);

		mAnimator->Play(L"Knight_SlashAltEffectright", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-20.0f, -90.0f));
		mCollider->SetSize(Vector2(120.0f, 90.0f));

		GameObject::Initialize();
	}

	void SlashAltEffectRight::Update()
	{
		GameObject::Update();
	}

	void SlashAltEffectRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SlashAltEffectRight::Release()
	{
		GameObject::Release();
	}

	void SlashAltEffectRight::slashAltEffectRightComplateEvent()
	{
		object::Destroy(this);
	}
}
