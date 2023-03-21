#include "LongFlatform.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidBody.h"

#include "yaPlayer.h"

namespace ya
{
	LongFlatform::LongFlatform()
	{

	}

	LongFlatform::~LongFlatform()
	{

	}

	void LongFlatform::Initialize()
	{
		//mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\room1.bmp");
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\GodHome\\Platform(Long)", Vector2::Zero, 1.0f);

		mAnimator->Play(L"GodHomePlatform(Long)", false);

		mCollider->SetSize(Vector2(1544.0f, 103.0f));
		mCollider->SetCenter(Vector2(-772.0f, -103.0f));

		GameObject::Initialize();
	}

	void LongFlatform::Update()
	{
		GameObject::Update();
	}

	void LongFlatform::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//BitBlt(hdc, tr->GetPos().x, tr->GetPos().y - 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void LongFlatform::Release()
	{
		GameObject::Release();
	}

	void LongFlatform::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();

			// 충돌한 콜라이더가 가속도로 인해 1프레임 사이에 콜라이더 안으로 들어갈 경우 콜라이더 위치 초기화
			// 상 하 좌 우 플레이어 벡터 방향에 따라 다르게 밀어내야 함
			Vector2 dir = mplayer->GetComponent<RigidBody>()->GetVelocity().Normalize();	// 플레이어 벡터 방향

			Collider* playerCol = mplayer->GetComponent<Collider>();
			Vector2 playerColPos = playerCol->GetPos();

			Collider* objectCol = this->GetComponent<Collider>();
			Vector2 objectColPos = objectCol->GetPos();

			Transform* playerTr = mplayer->GetComponent<Transform>();
			Transform* objectTr = this->GetComponent<Transform>();

			Vector2 playerPos = playerTr->GetPos();
			Vector2 objectPos = objectTr->GetPos();

			float fXLen = fabs(playerColPos.x - objectColPos.x);
			float fXSize = (playerCol->GetSize().x / 2.0f) + (objectCol->GetSize().x / 2.0f);
			float fYLen = fabs(playerColPos.y - objectColPos.y);
			float fYSize = (playerCol->GetSize().y / 2.0f) + (objectCol->GetSize().y / 2.0f);

			// 뚫고 넘어가는 문제는 픽셀 충돌 이후로 수정
			// 플레이어 현재 좌표 파악해서 다르게 적용해야 함
			// to up
			if (0.0f > dir.y && dir.y >= -1.0f)
			{
				if (fYLen < fYSize)
				{
					playerPos.y = objectColPos.y + this->GetComponent<Collider>()->GetSize().y + playerCol->GetSize().y;
					playerTr->SetPos(playerPos);
				}
			}

			// to down
			else if (0.0f < dir.y && dir.y <= 1.0f)
			{
				if (fYLen < fYSize)
				{
					playerPos.y = objectColPos.y;
					playerTr->SetPos(playerPos);
				}

				rb->SetGround(true);
				mplayer->SetPlayerState(Player::ePlayerState::Idle);
			}
			// to right
			else if (0.0f < dir.x && dir.x <= 1.0f)
			{
				if (fXLen < fXSize)
				{
					playerPos.x = objectColPos.x - playerCol->GetSize().x / 2.0f;
					playerTr->SetPos(playerPos);
				}
			}

			// to left
			// dir >= -1
			else if (0.0f > dir.x && dir.x >= -1.0f)
			{
				if (fXLen > fXSize)
				{
					playerPos.x = objectColPos.x + objectCol->GetSize().x + (playerCol->GetSize().x / 2.0f);
					playerTr->SetPos(playerPos);
				}
			}

			
		}
	}

	void LongFlatform::OnCollisionStay(Collider* other)
	{
		
	}

	void LongFlatform::OnCollisionExit(Collider* other)
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