#include "yaSlashAltEffectLeft.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"

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
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAltEffect\\left", Vector2::Zero, 0.1f);

		mAnimator->Play(L"Knight_SlashAltEffectleft", false);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-60.0f, -80.0f));
		mCollider->SetSize(Vector2(120.0f, 60.0f));

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
}
