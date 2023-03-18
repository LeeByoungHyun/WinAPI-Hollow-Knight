#include "DoubleJumpEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaTransform.h"

namespace ya
{
	DoubleJumpEffect::DoubleJumpEffect()
	{

	}

	DoubleJumpEffect::~DoubleJumpEffect()
	{

	}

	void DoubleJumpEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		tr = GetComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DoubleJumpEffect\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DoubleJumpEffect\\right", Vector2::Zero, 0.1f);
		mAnimator->GetCompleteEvent(L"Knight_DoubleJumpEffectleft") = std::bind(&DoubleJumpEffect::doubleJumpEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_DoubleJumpEffectright") = std::bind(&DoubleJumpEffect::doubleJumpEffectComplateEvent, this);

		if (player->GetPlayerDirection() == Player::eDirection::Left)
			mAnimator->Play(L"Knight_DoubleJumpEffectleft", false);

		else if (player->GetPlayerDirection() == Player::eDirection::Right)
			mAnimator->Play(L"Knight_DoubleJumpEffectright", false);

		GameObject::Initialize();
	}

	void DoubleJumpEffect::Update()
	{
		if ((player->GetPlayerState() != Player::ePlayerState::DoubleJump))
			object::Destroy(this);

		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			Vector2 corPos = Vector2(75.0f, 210.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			Vector2 corPos = Vector2(95.0f, 210.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		GameObject::Update();
	}

	void DoubleJumpEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void DoubleJumpEffect::Release()
	{
		GameObject::Release();
	}

	void DoubleJumpEffect::doubleJumpEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
