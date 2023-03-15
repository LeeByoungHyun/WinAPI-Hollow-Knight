#include "yaDashEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"

namespace ya
{
	DashEffectRight::DashEffectRight()
	{
		mAnimator = AddComponent<Animator>();
	}

	DashEffectRight::~DashEffectRight()
	{

	}

	void DashEffectRight::Initialize()
	{
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DashEffect\\right", Vector2::Zero, 0.05f);
		mAnimator->GetCompleteEvent(L"Knight_DashEffectright") = std::bind(&DashEffectRight::dashEffectRightComplateEvent, this);
		mAnimator->Play(L"Knight_DashEffectright", true);

		GameObject::Initialize();
	}

	void DashEffectRight::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		pos.x += 800.0f * Time::DeltaTime();

		tr->SetPos(pos);

		GameObject::Update();
	}

	void DashEffectRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void DashEffectRight::Release()
	{
		GameObject::Release();
	}

	void DashEffectRight::dashEffectRightComplateEvent()
	{
		object::Destroy(this);
	}
}
