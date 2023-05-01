#include "SlashEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"
#include "NailHitEffect.h"

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
		tr->SetSize(Vector2(1.5f, 1.5f));

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashEffect\\left", Vector2::Zero, 0.015f);
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_SlashEffect\\right", Vector2::Zero, 0.015f);

		mAnimator->GetCompleteEvent(L"Knight_SlashEffectleft") = std::bind(&SlashEffect::slashEffectComplateEvent, this);
		mAnimator->GetCompleteEvent(L"Knight_SlashEffectright") = std::bind(&SlashEffect::slashEffectComplateEvent, this);

		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			mAnimator->Play(L"Knight_SlashEffectleft", false);
			mCollider->SetCenter(Vector2(-70.0f, -100.0f));
			mCollider->SetSize(Vector2(180.0f, 135.0f));
		}
		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			mAnimator->Play(L"Knight_SlashEffectright", false);
			mCollider->SetCenter(Vector2(-35.0f, -100.0f));
			mCollider->SetSize(Vector2(180.0f, 135.0f));
		}

		GameObject::Initialize();
	}

	void SlashEffect::Update()
	{
		if (player->GetPlayerDirection() == Player::eDirection::Left)
		{
			Vector2 corPos = Vector2(-138.0f, -30.0f);
			tr->SetPos(player->GetPos() + corPos);
		}

		else if (player->GetPlayerDirection() == Player::eDirection::Right)
		{
			Vector2 corPos = Vector2(60.0f, -30.0f);
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

	void SlashEffect::OnCollisionStay(Collider* other)
	{
		
	}

	void SlashEffect::OnCollisionExit(Collider* other)
	{

	}

	void SlashEffect::slashEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
