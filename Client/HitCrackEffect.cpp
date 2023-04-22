#include "HitCrackEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	HitCrackEffect::HitCrackEffect()
	{

	}

	HitCrackEffect::~HitCrackEffect()
	{

	}

	void HitCrackEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\Hit_Creck\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Hit_Creckneutral") = std::bind(&HitCrackEffect::hitCrackEffectComplateEvent, this);

		GameObject::Initialize();
	}

	void HitCrackEffect::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//pos.x -= 800.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (playFlag == false)
		{
			mAnimator->Play(L"Hit_Creckneutral", false);
			playFlag = true;
		}

		GameObject::Update();
	}

	void HitCrackEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HitCrackEffect::Release()
	{
		GameObject::Release();
	}

	void HitCrackEffect::hitCrackEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
