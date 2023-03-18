#include "FocusEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	FocusEffect::FocusEffect()
	{

	}

	FocusEffect::~FocusEffect()
	{

	}

	void FocusEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusEffect\\neutral", Vector2::Zero, 0.075f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_FocusEndEffect\\neutral", Vector2::Zero, 0.1f);
		mAnimator->GetCompleteEvent(L"Knight_FocusEffectneutral") = std::bind(&FocusEffect::focusEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_FocusEndEffectneutral") = std::bind(&FocusEffect::focusEndEffectComplateEvent, this);
		mAnimator->Play(L"Knight_FocusEffectneutral", false);

		GameObject::Initialize();
	}

	void FocusEffect::Update()
	{
		if ((player->GetPlayerState() != Player::ePlayerState::FocusGet) && (player->GetPlayerState() != Player::ePlayerState::Focus))
		{
			if (endFlag == false)
			{
				mAnimator->Play(L"Knight_FocusEndEffectneutral", false);
				endFlag = true;
			}
		}

		GameObject::Update();
	}

	void FocusEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void FocusEffect::Release()
	{
		GameObject::Release();
	}

	void FocusEffect::focusEffectComplateEvent()
	{
		object::Destroy(this);
	}

	void FocusEffect::focusEndEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
