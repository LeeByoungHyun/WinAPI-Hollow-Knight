#include "StunEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	StunEffect::StunEffect()
	{

	}

	StunEffect::~StunEffect()
	{

	}

	void StunEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\Stun\\neutral", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"Stunneutral") = std::bind(&StunEffect::StunEffectComplateEvent, this);

		GameObject::Initialize();
	}

	void StunEffect::Update()
	{
		Vector2 pos = Player::GetInstance()->GetComponent<Transform>()->GetPos();
		pos.y += 50.0f;
		tr->SetPos(pos);

		if (playFlag == false)
		{
			mAnimator->Play(L"Stunneutral", false);
			playFlag = true;
		}

		GameObject::Update();
	}

	void StunEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void StunEffect::Release()
	{
		GameObject::Release();
	}

	void StunEffect::StunEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
