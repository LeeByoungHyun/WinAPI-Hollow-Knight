#include "yaUpSlashEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"

namespace ya
{
	UpSlashEffect::UpSlashEffect()
	{

	}

	UpSlashEffect::~UpSlashEffect()
	{

	}

	void UpSlashEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_UpSlashEffect\\neutral", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"Knight_UpSlashEffectneutral") = std::bind(&UpSlashEffect::upSlashEffectComplateEvent, this);

		mAnimator->Play(L"Knight_UpSlashEffectneutral", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetCenter(Vector2(-60.0f, -180.0f));
		mCollider->SetSize(Vector2(120.0f, 150.0f));

		GameObject::Initialize();
	}

	void UpSlashEffect::Update()
	{
		GameObject::Update();
	}

	void UpSlashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void UpSlashEffect::Release()
	{
		GameObject::Release();

	}

	void UpSlashEffect::upSlashEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
