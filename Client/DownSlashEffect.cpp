#include "DownSlashEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"

namespace ya
{
	DownSlashEffect::DownSlashEffect()
	{

	}

	DownSlashEffect::~DownSlashEffect()
	{

	}

	void DownSlashEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		Collider* mCollider = AddComponent<Collider>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DownSlashEffect\\neutral", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"Knight_DownSlashEffectneutral") = std::bind(&DownSlashEffect::downSlashEffectComplateEvent, this);

		mAnimator->Play(L"Knight_DownSlashEffectneutral", false);

		mCollider->SetCenter(Vector2(-60.0f, -165.0f));
		mCollider->SetSize(Vector2(120.0f, 150.0f));

		GameObject::Initialize();
	}

	void DownSlashEffect::Update()
	{
		Vector2 corPos = Vector2(0.0f, 70.0f);
		tr->SetPos(player->GetPos() + corPos);

		GameObject::Update();
	}

	void DownSlashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DownSlashEffect::Release()
	{
		GameObject::Release();

	}

	void DownSlashEffect::downSlashEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
