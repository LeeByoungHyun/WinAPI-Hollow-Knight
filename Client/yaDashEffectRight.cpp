#include "yaDashEffectRight.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	DashEffectRight::DashEffectRight()
	{

	}

	DashEffectRight::~DashEffectRight()
	{

	}

	void DashEffectRight::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DashEffect\\right", Vector2::Zero, 0.033f);
		mAnimator->GetCompleteEvent(L"Knight_DashEffectright") = std::bind(&DashEffectRight::dashEffectRightComplateEvent, this);
		mAnimator->Play(L"Knight_DashEffectright", true);

		GameObject::Initialize();
	}

	void DashEffectRight::Update()
	{
		if (player->GetPlayerState() != Player::ePlayerState::Dash)
			object::Destroy(this);

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
