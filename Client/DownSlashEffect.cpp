#include "DownSlashEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"
#include "yaRigidBody.h"

namespace ya
{
	DownSlashEffect::DownSlashEffect()
	{

	}

	DownSlashEffect::~DownSlashEffect()
	{

	}

	void DownSlashEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		Collider* mCollider = AddComponent<Collider>();
		tr = AddComponent<Transform>();
		tr->SetSize(Vector2(1.2f, 1.2f));

		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DownSlashEffect\\neutral", Vector2::Zero, 0.033f);

		mAnimator->GetCompleteEvent(L"Knight_DownSlashEffectneutral") = std::bind(&DownSlashEffect::downSlashEffectComplateEvent, this);

		mAnimator->Play(L"Knight_DownSlashEffectneutral", false);

		mCollider->SetCenter(Vector2(-60.0f, -165.0f));
		mCollider->SetSize(Vector2(160.0f, 180.0f));

		GameObject::Initialize();
	}

	void DownSlashEffect::Update()
	{
		Vector2 corPos = Vector2(-36.0f, 112.0f);
		tr->SetPos(player->GetPos() + corPos);

		GameObject::Update();
	}

	void DownSlashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DownSlashEffect::Release()
	{
		GameObject::Release();

	}

	void DownSlashEffect::OnCollisionEnter(Collider* other)
	{

	}

	void DownSlashEffect::OnCollisionStay(Collider* other)
	{
		// 몬스터와 충돌시 1회에 한해 뒤로 넉백 + 충돌한 몬스터 체력 감소
		if ((other->GetOwner()->GetType() == eLayerType::Monster) && hitFlag == false)
		{
			Vector2 pos = player->GetPos();
			player->GetComponent<RigidBody>()->SetVelocity(Vector2(0.0f, -400.0f));

			hitFlag = true;
		}
	}

	void DownSlashEffect::OnCollisionExit(Collider* other)
	{

	}

	void DownSlashEffect::downSlashEffectComplateEvent()
	{
		object::Destroy(this);
	}
}
