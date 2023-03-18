#include "FireballCastEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaTransform.h"

namespace ya
{
	FireballCastEffectRight::FireballCastEffectRight()
	{

	}

	FireballCastEffectRight::~FireballCastEffectRight()
	{

	}

	void FireballCastEffectRight::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		tr = GetComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballCastEffect\\right", Vector2::Zero, 0.033f);
		mAnimator->GetCompleteEvent(L"Knight_FireballCastEffectright") = std::bind(&FireballCastEffectRight::fireballCastEffectComplateEvent, this);

		mAnimator->Play(L"Knight_FireballCastEffectright", false);
		tr->SetSize(Vector2(0.7f, 0.7f));

		GameObject::Initialize();
	}

	void FireballCastEffectRight::Update()
	{
		if ((player->GetPlayerState() != Player::ePlayerState::CastFireball))
			object::Destroy(this);

		Vector2 corPos = Vector2(0.0f, 110.0f);
		tr->SetPos(player->GetPos() + corPos);

		GameObject::Update();
	}

	void FireballCastEffectRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void FireballCastEffectRight::Release()
	{
		GameObject::Release();
	}

	void FireballCastEffectRight::fireballCastEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
