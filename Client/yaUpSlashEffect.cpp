#include "yaUpSlashEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"

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
		player = Player::GetInstance();
		Collider* mCollider = AddComponent<Collider>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_UpSlashEffect\\neutral", Vector2::Zero, 0.015f);

		mAnimator->GetCompleteEvent(L"Knight_UpSlashEffectneutral") = std::bind(&UpSlashEffect::upSlashEffectComplateEvent, this);

		mAnimator->Play(L"Knight_UpSlashEffectneutral", true);

		mCollider->SetCenter(Vector2(-60.0f, -180.0f));
		mCollider->SetSize(Vector2(120.0f, 150.0f));

		GameObject::Initialize();
	}

	void UpSlashEffect::Update()
	{
		Vector2 corPos = Vector2(0.0f, 0.0f);
		tr->SetPos(player->GetPos() + corPos);

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
