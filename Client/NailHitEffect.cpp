#include "NailHitEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	NailHitEffect::NailHitEffect()
	{

	}

	NailHitEffect::~NailHitEffect()
	{

	}

	void NailHitEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();
		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\Nail Hit\\left", Vector2::Zero, 0.016f);
		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\Nail Hit\\right", Vector2::Zero, 0.016f);

		mAnimator->GetCompleteEvent(L"Nail Hitleft") = std::bind(&NailHitEffect::nailHitEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Nail Hitright") = std::bind(&NailHitEffect::nailHitEffectComplateEvent, this);

		tr->SetSize(Vector2(2.0f, 2.0f));

		GameObject::Initialize();
	}

	void NailHitEffect::Update()
	{
		if (playFlag == false)
		{
			Vector2 pos = tr->GetPos();
			if (Player::GetInstance()->GetPlayerDirection() == Player::eDirection::Left)
			{
				pos.x -= 250.0f;
				pos.y -= 90.0f;
				mAnimator->Play(L"Nail Hitleft", false);
			}
			else
			{
				pos.y -= 90.0f;
				mAnimator->Play(L"Nail Hitright", false);
			}
			playFlag = true;

			tr->SetPos(pos);
		}

		GameObject::Update();
	}

	void NailHitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void NailHitEffect::Release()
	{
		GameObject::Release();
	}

	void NailHitEffect::nailHitEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
