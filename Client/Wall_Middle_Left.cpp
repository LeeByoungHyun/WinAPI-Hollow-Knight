#include "Wall_Middle_Left.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidBody.h"
#include "yaImage.h"
#include "yaCamera.h"

#include "yaPlayer.h"
#include "Hornet.h"
#include "FalseKnight.h"

namespace ya
{
	Wall_Middle_Left::Wall_Middle_Left()
	{

	}

	Wall_Middle_Left::~Wall_Middle_Left()
	{

	}

	void Wall_Middle_Left::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"Wall_Middle_Left", L"..\\Resources\\GodHome\\Wall_middle_left.bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(76.0f, 466.0f));
		mCollider->SetCenter(Vector2(-38.0f, -466.0f));

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void Wall_Middle_Left::Update()
	{
		GameObject::Update();
	}

	void Wall_Middle_Left::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// 카메라 위치에 맞추어 좌표 계산
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);
		pos.x -= mImage->GetWidth() / 2;
		pos.y -= mImage->GetHeight();

		TransparentBlt(hdc, pos.x, pos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));
	}

	void Wall_Middle_Left::Release()
	{
		GameObject::Release();
	}

	void Wall_Middle_Left::OnCollisionEnter(Collider* other)
	{
		
	}

	void Wall_Middle_Left::OnCollisionStay(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();

			Vector2 dir = mplayer->GetComponent<RigidBody>()->GetVelocity().Normalize();	// 플레이어 벡터 방향

			Collider* playerCol = mplayer->GetComponent<Collider>();
			Vector2 playerColPos = playerCol->GetPos();
			Collider* objectCol = this->GetComponent<Collider>();
			Vector2 objectColPos = objectCol->GetPos();
			Transform* playerTr = mplayer->GetComponent<Transform>();
			Transform* objectTr = this->GetComponent<Transform>();
			Vector2 playerPos = playerTr->GetPos();
			Vector2 objectPos = objectTr->GetPos();

			// to right
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더 사이에 있고,
			// 충돌시 플레이어 x좌표가 오브젝트 콜라이더보다 왼쪽에 있을때만 적용
			if ((0 < dir.x && dir.x <= 1)	// 벡터방향이 right일 경우
				&& playerPos.x < objectPos.x - objectCol->GetSize().x / 2
				&& playerPos.y - playerCol->GetSize().y < objectPos.y
				&& playerPos.y > objectPos.y - objectCol->GetSize().y)
			{
				playerPos.x = objectPos.x - objectCol->GetSize().x / 2 - playerCol->GetSize().x / 2 + 1.0f;
				playerTr->SetPos(playerPos);

				return;
			}
			// to left
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더 사이에 있고,
			// 플레이어 x좌표가 오브젝트 콜라이더보다 오른쪽에 있을때만 적용
			if ((0 > dir.x && dir.x >= -1)	// 벡터방향이 left일 경우
				&& playerPos.x > objectPos.x + objectCol->GetSize().x / 2
				&& playerPos.y - playerCol->GetSize().y < objectPos.y
				&& playerPos.y > objectPos.y - objectCol->GetSize().y)
			{
				playerPos.x = objectPos.x + objectCol->GetSize().x / 2 + playerCol->GetSize().x / 2 - 1.0f;
				playerTr->SetPos(playerPos);

				if (rb->GetGround() != true && mplayer->GetPlayerState() != Player::ePlayerState::WallJump
					&& (0 < dir.y && dir.y <= 1))
				{
					mplayer->SetPlayerState(Player::ePlayerState::WallSlide);
					mplayer->SetFallFlag(false);
				}
				return;
			}
			// to up
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더보다 아래에 있고,
			// 플레이어 x좌표가 오브젝트콜라이더 사이에 위치한 경우 아래로 밀어냄
			if ((0 > dir.y && dir.y >= -1)	// 벡터방향이 up일 경우
				&& playerPos.y - playerCol->GetSize().y < objectPos.y
				&& playerPos.y > objectPos.y
				&& playerPos.x > objectPos.x - objectCol->GetSize().x
				&& playerPos.x < objectPos.x + objectCol->GetSize().x)
			{
				if (mplayer->GetPlayerState() == Player::ePlayerState::WallJump)
					return;
				playerPos.y = objectPos.y + playerCol->GetSize().y - 1.0f;
				playerTr->SetPos(playerPos);
				return;
			}
			// to down
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더보다 위에 있고,
			// 플레이어 x좌표가 오브젝트콜라이더 사이에 위치한 경우에만 적용
			if ((0 < dir.y && dir.y <= 1)	// 벡터방향이 down일 경우
				&& playerPos.y > objectPos.y - objectCol->GetSize().y
				&& playerPos.y - playerCol->GetSize().y < objectPos.y - objectCol->GetSize().y
				&& playerPos.x > objectPos.x - objectCol->GetSize().x
				&& playerPos.x < objectPos.x + objectCol->GetSize().x)
			{
				if (mplayer->GetPlayerState() == Player::ePlayerState::WallJump)
					return;
				playerPos.y = objectPos.y - objectCol->GetSize().y + 1;
				playerTr->SetPos(playerPos);
				rb->SetGround(true);
				mplayer->SetPlayerState(Player::ePlayerState::Idle);
				return;
			}
		}
	}

	void Wall_Middle_Left::OnCollisionExit(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();
			if (mplayer->GetPlayerState() != Player::ePlayerState::WallJump)
				mplayer->SetPlayerState(Player::ePlayerState::Idle);
			rb->SetGround(false);
		}
	}
}