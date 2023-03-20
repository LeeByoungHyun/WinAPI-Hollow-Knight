#include "GroundCollider.h"
#include "yaCollider.h"
#include "yaRigidbody.h"
#include "yaTransform.h"

#include "yaPlayer.h"

namespace ya
{
	GroundCollider::GroundCollider()
	{
	}

	GroundCollider::~GroundCollider()
	{
	}

	void GroundCollider::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1600.0f, 50.0f));
		GameObject::Initialize();
	}

	void GroundCollider::Update()
	{
		GameObject::Update();
	}

	void GroundCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void GroundCollider::Release()
	{
	}

	void GroundCollider::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();
			rb->SetGround(true);

			Collider* cupheadCol = mplayer->GetComponent<Collider>();
			Vector2 cupheadPos = cupheadCol->GetPos();

			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 groundPos = groundCol->GetPos();

			float fLen = fabs(cupheadPos.y - groundPos.y);
			float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

			// 충돌한 콜라이더가 가속도로 인해 1프레임 사이에 콜라이더 안으로 들어갈 경우 콜라이더 위치 초기화
			if (fLen < fSize)
			{
				Transform* playerTr = mplayer->GetComponent<Transform>();
				Transform* grTr = this->GetComponent<Transform>();

				Vector2 playerPos = playerTr->GetPos();
				Vector2 grPos = grTr->GetPos();

				playerPos -= (fSize - fLen) - 1.0f;
				playerTr->SetPos(playerPos);
			}
		}
	}

	void GroundCollider::OnCollisionStay(Collider* other)
	{

	}

	void GroundCollider::OnCollisionExit(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();
			rb->SetGround(false);
		}
	}
}
