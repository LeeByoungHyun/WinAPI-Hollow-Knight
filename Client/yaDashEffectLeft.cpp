#include "yaDashEffectLeft.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaPlayer.h"

namespace ya
{
	DashEffectLeft::DashEffectLeft()
	{

	}

	DashEffectLeft::~DashEffectLeft()
	{

	}

	void DashEffectLeft::Initialize()
	{
		player = Player::GetInstance();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DashEffect\\left", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"Knight_DashEffectleft") = std::bind(&DashEffectLeft::dashEffectLeftComplateEvent, this);

		mAnimator->Play(L"Knight_DashEffectleft", true);

		GameObject::Initialize();
	}

	void DashEffectLeft::Update()
	{
		if (player->GetPlayerState() != Player::ePlayerState::Dash)
			object::Destroy(this);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x -= 800.0f * Time::DeltaTime();
		tr->SetPos(pos);

		GameObject::Update();
	}

	void DashEffectLeft::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void DashEffectLeft::Release()
	{
		GameObject::Release();
	}

	void DashEffectLeft::dashEffectLeftComplateEvent()
	{
		object::Destroy(this);
	}
}
