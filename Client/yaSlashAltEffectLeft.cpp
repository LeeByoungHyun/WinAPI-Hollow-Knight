#include "yaSlashAltEffectLeft.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"

namespace ya
{
	SlashAltEffectLeft::SlashAltEffectLeft()
	{

	}

	SlashAltEffectLeft::~SlashAltEffectLeft()
	{

	}

	void SlashAltEffectLeft::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAltEffect\\left", Vector2::Zero, 0.05f);

		mAnimator->GetCompleteEvent(L"Knight_SlashAltEffectleft") = std::bind(&SlashAltEffectLeft::slashAltEffectLeftComplateEvent, this);

		mAnimator->Play(L"Knight_SlashAltEffectleft", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-100.0f, -90.0f));
		mCollider->SetSize(Vector2(120.0f, 90.0f));

		GameObject::Initialize();
	}

	void SlashAltEffectLeft::Update()
	{
		GameObject::Update();
	}

	void SlashAltEffectLeft::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SlashAltEffectLeft::Release()
	{
		GameObject::Release();

	}

	void SlashAltEffectLeft::slashAltEffectLeftComplateEvent()
	{
		object::Destroy(this);
	}
}
