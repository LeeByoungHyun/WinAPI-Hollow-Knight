#include "SlashAltEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"
#include "NailHitEffect.h"

namespace ya
{
	SlashAltEffect::SlashAltEffect()
	{

	}

	SlashAltEffect::~SlashAltEffect()
	{

	}

	void SlashAltEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		Collider* mCollider = AddComponent<Collider>();
		tr = AddComponent<Transform>();
		tr->SetSize(Vector2(1.5f, 1.5f));

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAltEffect\\left", Vector2::Zero, 0.015f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashAltEffect\\right", Vector2::Zero, 0.015f);

		mAnimator->GetCompleteEvent(L"Knight_SlashAltEffectleft") = std::bind(&SlashAltEffect::slashAltEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashAltEffectright") = std::bind(&SlashAltEffect::slashAltEffectComplateEvent, this);

		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			mAnimator->Play(L"Knight_SlashAltEffectleft", false);
			mCollider->SetCenter(Vector2(-100.0f, -90.0f));
			mCollider->SetSize(Vector2(180.0f, 135.0f));
		}
		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			mAnimator->Play(L"Knight_SlashAltEffectright", false);
			mCollider->SetCenter(Vector2(25.0f, -90.0f));
			mCollider->SetSize(Vector2(180.0f, 135.0f));
		}

		GameObject::Initialize();
	}

	void SlashAltEffect::Update()
	{
		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			Vector2 corPos = Vector2(-110.0f, -40.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			Vector2 corPos = Vector2(0.0f, -40.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		GameObject::Update();
	}

	void SlashAltEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SlashAltEffect::Release()
	{
		GameObject::Release();
	}

	void SlashAltEffect::OnCollisionEnter(Collider* other)
	{

	}

	void SlashAltEffect::OnCollisionStay(Collider* other)
	{
		// 몬스터와 충돌시 1회에 한해 뒤로 넉백 + 충돌한 몬스터 체력 감소
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
			object::Instantiate<NailHitEffect>(tr->GetPos(), eLayerType::Effect);

			hitFlag = true;
		}

		if ((other->GetOwner()->GetType() == eLayerType::FalseKnight) && hitFlag == false)
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
			object::Instantiate<NailHitEffect>(tr->GetPos(), eLayerType::Effect);

			hitFlag = true;
		}

		if ((other->GetOwner()->GetType() == eLayerType::Hornet) && hitFlag == false)
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
			object::Instantiate<NailHitEffect>(tr->GetPos(), eLayerType::Effect);

			hitFlag = true;
		}
	}

	void SlashAltEffect::OnCollisionExit(Collider* other)
	{
	}

	void SlashAltEffect::slashAltEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
