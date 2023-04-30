#include "FireballHitEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	FireballHitEffect::FireballHitEffect()
	{

	}

	FireballHitEffect::~FireballHitEffect()
	{

	}

	void FireballHitEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();
		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\FireballHit\\left", Vector2::Zero, 0.016f);
		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\FireballHit\\right", Vector2::Zero, 0.016f);

		mAnimator->GetCompleteEvent(L"FireballHitleft") = std::bind(&FireballHitEffect::FireballHitEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"FireballHitright") = std::bind(&FireballHitEffect::FireballHitEffectComplateEvent, this);

		tr->SetSize(Vector2(1.2f, 1.2f));

		GameObject::Initialize();
	}

	void FireballHitEffect::Update()
	{
		if (playFlag == false)
		{
			Vector2 pos = tr->GetPos();
			if (Player::GetInstance()->GetPlayerDirection() == Player::eDirection::Left)
			{
				//pos.x -= 250.0f;
				//pos.y -= 90.0f;
				mAnimator->Play(L"FireballHitleft", false);
			}
			else
			{
				//pos.y -= 90.0f;
				mAnimator->Play(L"FireballHitright", false);
			}
			playFlag = true;

			tr->SetPos(pos);
		}

		GameObject::Update();
	}

	void FireballHitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FireballHitEffect::Release()
	{
		GameObject::Release();
	}

	void FireballHitEffect::FireballHitEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
