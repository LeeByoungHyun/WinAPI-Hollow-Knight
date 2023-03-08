#include "yaSlashAltEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"

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
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAltEffect\\right", Vector2::Zero, 0.1f);

		mAnimator->Play(L"Knight_SlashAltEffectright", false);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-60.0f, -80.0f));
		mCollider->SetSize(Vector2(120.0f, 60.0f));

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
}
