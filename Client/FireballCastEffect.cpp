#include "FireballCastEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaTransform.h"

namespace ya
{
	FireballCastEffect::FireballCastEffect()
	{

	}

	FireballCastEffect::~FireballCastEffect()
	{

	}

	void FireballCastEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		tr = GetComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballCastEffect\\left", Vector2::Zero, 0.033f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FireballCastEffect\\right", Vector2::Zero, 0.033f);
		mAnimator->GetCompleteEvent(L"Knight_FireballCastEffectleft") = std::bind(&FireballCastEffect::fireballCastEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FireballCastEffectright") = std::bind(&FireballCastEffect::fireballCastEffectComplateEvent, this);

		if (player->GetPlayerDirection() == Player::eDirection::Left)
			mAnimator->Play(L"Knight_FireballCastEffectleft", false);

		else if (player->GetPlayerDirection() == Player::eDirection::Right)
			mAnimator->Play(L"Knight_FireballCastEffectright", false);

		tr->SetSize(Vector2(0.7f, 0.7f));

		GameObject::Initialize();
	}

	void FireballCastEffect::Update()
	{
		if ((player->GetPlayerState() != Player::ePlayerState::CastFireball))
			object::Destroy(this);

		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			Vector2 corPos = Vector2(0.0f, 110.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			Vector2 corPos = Vector2(80.0f, 110.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		GameObject::Update();
	}

	void FireballCastEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void FireballCastEffect::Release()
	{
		GameObject::Release();
	}

	void FireballCastEffect::fireballCastEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
