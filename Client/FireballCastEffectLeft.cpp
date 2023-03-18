#include "FireballCastEffectLeft.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaTransform.h"

namespace ya
{
	FireballCastEffectLeft::FireballCastEffectLeft()
	{

	}

	FireballCastEffectLeft::~FireballCastEffectLeft()
	{

	}

	void FireballCastEffectLeft::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		tr = GetComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballCastEffect\\left", Vector2::Zero, 0.033f);
		mAnimator->GetCompleteEvent(L"Knight_FireballCastEffectleft") = std::bind(&FireballCastEffectLeft::fireballCastEffectComplateEvent, this);

		mAnimator->Play(L"Knight_FireballCastEffectleft", false);
		tr->SetSize(Vector2(0.7f, 0.7f));

		GameObject::Initialize();
	}

	void FireballCastEffectLeft::Update()
	{
		if ((player->GetPlayerState() != Player::ePlayerState::CastFireball))
			object::Destroy(this);

		Vector2 corPos = Vector2(0.0f, 110.0f);
		tr->SetPos(player->GetPos() + corPos);

		GameObject::Update();
	}

	void FireballCastEffectLeft::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void FireballCastEffectLeft::Release()
	{
		GameObject::Release();
	}

	void FireballCastEffectLeft::fireballCastEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
