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
		
	}

	void TestCollider::OnCollisionStay(Collider* other)
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
			if ((0 < dir.x && dir.x <= 1)	// 벡터방향이 right일 경우
				)
			{
				playerPos.x -= 1.0f;
				playerTr->SetPos(playerPos);
			}

			// to left
			if ((0 > dir.x && dir.x >= -1)	// 벡터방향이 left일 경우
				)
			{
	
				playerPos.x += 1.0f;
				playerTr->SetPos(playerPos);
			}

			// to up
			if ((0 > dir.y && dir.y >= -1)	// 벡터방향이 up일 경우
				&& playerColPos.y <= objectColPos.y + objectCol->GetSize().y)
			{
				if (playerColPos.y + playerCol->GetSize().y <= objectColPos.y + objectCol->GetSize().y / 2)
					return;

				playerPos.y = playerCol->GetSize().y + objectColPos.y + objectCol->GetSize().y;
				//playerPos.y += 1.0f * Time::DeltaTime();
				playerTr->SetPos(playerPos);
			}

			// to down
			if ((0 < dir.y && dir.y <= 1)	// 벡터방향이 down일 경우
				&& playerColPos.y + playerCol->GetSize().y >= objectColPos.y)
			{
				if (playerColPos.y + playerCol->GetSize().y >= objectColPos.y + objectCol->GetSize().y / 2)
					return;

				playerPos.y -= 1.0f;
				playerTr->SetPos(playerPos);

				if (mplayer->GetIdleFlag() == false)
				{
					rb->SetGround(true);
					mplayer->SetPlayerState(Player::ePlayerState::Idle);
				}
			}
		}
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