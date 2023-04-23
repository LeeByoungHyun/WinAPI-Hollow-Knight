#include "ExplodeBarrelEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	ExplodeBarrelEffect::ExplodeBarrelEffect()
	{

	}

	ExplodeBarrelEffect::~ExplodeBarrelEffect()
	{

	}

	void ExplodeBarrelEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\BarrelExplode\\neutral", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"BarrelExplodeneutral") = std::bind(&ExplodeBarrelEffect::ExplodeBarrelEffectComplateEvent, this);

		GameObject::Initialize();
	}

	void ExplodeBarrelEffect::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//pos.x -= 800.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (playFlag == false)
		{
			mAnimator->Play(L"BarrelExplodeneutral", false);
			playFlag = true;
		}

		GameObject::Update();
	}

	void ExplodeBarrelEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ExplodeBarrelEffect::Release()
	{
		GameObject::Release();
	}

	void ExplodeBarrelEffect::ExplodeBarrelEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
