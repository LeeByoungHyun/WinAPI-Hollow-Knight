#include "SlashEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"

namespace ya
{
	SlashEffect::SlashEffect()
	{

	}

	SlashEffect::~SlashEffect()
	{

	}

	void SlashEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		Collider* mCollider = AddComponent<Collider>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashEffect\\left", Vector2::Zero, 0.015f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashEffect\\right", Vector2::Zero, 0.015f);

		mAnimator->GetCompleteEvent(L"Knight_SlashEffectleft") = std::bind(&SlashEffect::slashEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashEffectright") = std::bind(&SlashEffect::slashEffectComplateEvent, this);

		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			mAnimator->Play(L"Knight_SlashEffectleft", false);
			mCollider->SetCenter(Vector2(-70.0f, -100.0f));
			mCollider->SetSize(Vector2(120.0f, 90.0f));
		}
		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			mAnimator->Play(L"Knight_SlashEffectright", false);
			mCollider->SetCenter(Vector2(-50.0f, -100.0f));
			mCollider->SetSize(Vector2(120.0f, 90.0f));
		}

		GameObject::Initialize();
	}

	void SlashEffect::Update()
	{
		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			Vector2 corPos = Vector2(-60.0f, 0.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			Vector2 corPos = Vector2(60.0f, 0.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		GameObject::Update();
	}

	void SlashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SlashEffect::Release()
	{
		GameObject::Release();
	}

	void SlashEffect::OnCollisionEnter(Collider* other)
	{

	}

	void SlashEffect::OnCollisionStay(Collider* other)
	{
		// ���Ϳ� �浹�� 1ȸ�� ���� �ڷ� �˹� + �浹�� ���� ü�� ����
		if ((other->GetOwner()->GetType() == eLayerType::Monster) && hitFlag == false)
		{
			Vector2 pos = player->GetPos();
			if (player->GetPlayerDirection() == Player::eDirection::Left)
			{
				player->SetPos(pos + Vector2(15.0f, 0.0f));
			}
			else if (player->GetPlayerDirection() == Player::eDirection::Right)
			{
				player->SetPos(pos + Vector2(-15.0f, 0.0f));
			}
			hitFlag = true;
		}
	}

	void SlashEffect::OnCollisionExit(Collider* other)
	{

	}

	void SlashEffect::slashEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
