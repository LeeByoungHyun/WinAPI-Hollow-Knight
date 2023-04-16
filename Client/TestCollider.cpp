#include "TestCollider.h"
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


namespace ya
{
	TestCollider::TestCollider()
	{

	}

	TestCollider::~TestCollider()
	{

	}

	void TestCollider::Initialize()
	{
		tr = AddComponent<Transform>();
		//mImage = ResourceManager::Load<Image>(L"Platform(Long)", L"..\\Resources\\GodHome\\Platform(Long).bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(700.0f, 100.0f));
		mCollider->SetCenter(Vector2(-350.0f, -100.0f));

		GameObject::Initialize();
	}

	void TestCollider::Update()
	{
		GameObject::Update();
	}

	void TestCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		/*
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
		*/

	}

	void TestCollider::Release()
	{
		GameObject::Release();
	}

	void TestCollider::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{

			/*
			if (mplayer->GetIdleFlag() == false)
			{
				rb->SetGround(true);
				mplayer->SetPlayerState(Player::ePlayerState::Idle);
				//mplayer->SetIdleFlag(true);
			}
			*/

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

			/*
			if (fYLen < fYSize)
			{
				playerPos.y = objectColPos.y;
				//playerPos -= (fYSize - fYLen);
				playerTr->SetPos(playerPos);

				if (mplayer->GetIdleFlag() == false)
				{
					rb->SetGround(true);
					mplayer->SetPlayerState(Player::ePlayerState::Idle);
				}
			}
			*/

			/*
			// to right
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더 사이에 있고,
			// 충돌시 플레이어 x좌표가 오브젝트 콜라이더보다 왼쪽에 있을때만 적용
			if ((0 < dir.x && dir.x <= 1)	// 벡터방향이 right일 경우
				&& (playerColPos.y + playerCol->GetSize().y > objectColPos.y)
				&& (playerColPos.y < objectColPos.y + objectCol->GetSize().y)
				&& (playerColPos.x + playerCol->GetSize().x > objectColPos.x))
			{
				if (fXLen < fXSize)
				{
					playerPos.x = objectColPos.x - (playerCol->GetSize().x / 2);
					playerTr->SetPos(playerPos);
				}

			}

			// to left
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더 사이에 있고,
			// 플레이어 x좌표가 오브젝트 콜라이더보다 오른쪽에 있을때만 적용
			if ((0 > dir.x && dir.x >= -1)	// 벡터방향이 left일 경우
				&& (playerColPos.y + playerCol->GetSize().y > objectColPos.y)
				&& (playerColPos.y < objectColPos.y + objectCol->GetSize().y)
				&& (playerColPos.x < objectColPos.x + objectCol->GetSize().x))
			{
				if (fXLen > fXSize)
				{
					playerPos.x = objectPos.x + objectCol->GetSize().x / 2.0f + 1;
					playerTr->SetPos(playerPos);
				}


			}

			// to up
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더보다 아래에 있고,
			// 플레이어 x좌표가 오브젝트콜라이더 사이에 위치한 경우 아래로 밀어냄
			if ((0 > dir.y && dir.y >= -1)	// 벡터방향이 up일 경우
				&& (playerColPos.y < objectColPos.y + objectCol->GetSize().y)
				&& (playerColPos.x + playerCol->GetSize().x >= objectColPos.x)
				&& (playerColPos.x < objectColPos.x + objectCol->GetSize().x))
			{
				if (fYLen < fYSize)
				{
					playerPos.y = objectPos.y + playerCol->GetSize().y;
					playerTr->SetPos(playerPos);
				}

			}

			// to down
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더보다 위에 있고,
			// 플레이어 x좌표가 오브젝트콜라이더 사이에 위치한 경우에만 적용
			if ((0 < dir.y && dir.y <= 1)	// 벡터방향이 down일 경우
				&& (playerColPos.y + playerCol->GetSize().y >= objectColPos.y)
				&& (playerColPos.x + playerCol->GetSize().x >= objectColPos.x)
				&& (playerColPos.x < objectColPos.x + objectCol->GetSize().x))
			{
				if (fYLen < fYSize)
				{
					playerPos.y = objectPos.y - playerCol->GetSize().y;
					playerTr->SetPos(playerPos);
				}

				if (mplayer->GetIdleFlag() == false)
				{
					rb->SetGround(true);
					mplayer->SetPlayerState(Player::ePlayerState::Idle);
				}

			}
			*/

			// to right
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더 사이에 있고,
			// 충돌시 플레이어 x좌표가 오브젝트 콜라이더보다 왼쪽에 있을때만 적용
			if ((0 < dir.x && dir.x <= 1))	// 벡터방향이 right일 경우
			{
				if (fXLen < fXSize)
				{
					if (playerColPos.y + playerCol->GetSize().y < objectColPos.y)
						return;
					if (playerColPos.y > objectColPos.y + objectCol->GetSize().y)
						return;

					playerPos.x = objectColPos.x - (playerCol->GetSize().x / 2);
					playerTr->SetPos(playerPos);
				}

			}

			// to left
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더 사이에 있고,
			// 플레이어 x좌표가 오브젝트 콜라이더보다 오른쪽에 있을때만 적용
			if ((0 > dir.x && dir.x >= -1))	// 벡터방향이 left일 경우
			{
				if (fXLen > fXSize)
				{
					if (true)
					{

					}
					playerPos.x = objectPos.x + objectCol->GetSize().x / 2.0f + 1;
					playerTr->SetPos(playerPos);
				}


			}

			// to up
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더보다 아래에 있고,
			// 플레이어 x좌표가 오브젝트콜라이더 사이에 위치한 경우 아래로 밀어냄
			if ((0 > dir.y && dir.y >= -1))	// 벡터방향이 up일 경우
			{
				if (fYLen < fYSize)
				{
					//if (playerColPos.y < objectColPos.y + objectCol->GetSize().y)
					//	return;

					playerPos.y = objectPos.y + playerCol->GetSize().y;
					playerTr->SetPos(playerPos);
				}

			}

			// to down
			// 충돌시 플레이어 y좌표가 오브젝트 콜라이더보다 위에 있고,
			// 플레이어 x좌표가 오브젝트콜라이더 사이에 위치한 경우에만 적용
			if ((0 < dir.y && dir.y <= 1))	// 벡터방향이 down일 경우
			{
				if (fYLen < fYSize)
				{
					playerPos.y = objectPos.y - playerCol->GetSize().y;
					playerTr->SetPos(playerPos);
				}

				if (mplayer->GetIdleFlag() == false)
				{
					rb->SetGround(true);
					mplayer->SetPlayerState(Player::ePlayerState::Idle);
				}

			}
		}
	}

	void TestCollider::OnCollisionStay(Collider* other)
	{

	}

	void TestCollider::OnCollisionExit(Collider* other)
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