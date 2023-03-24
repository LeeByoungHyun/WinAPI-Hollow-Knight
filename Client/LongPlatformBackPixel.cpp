#include "LongPlatformBackPixel.h"
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
	LongPlatformBackPixel::LongPlatformBackPixel()
	{

	}

	LongPlatformBackPixel::~LongPlatformBackPixel()
	{

	}

	void LongPlatformBackPixel::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"Platform(Long)_BackPiel", L"..\\Resources\\GodHome\\Platform(Long)_BackPixel.bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1544.0f, 99.0f));
		mCollider->SetCenter(Vector2(-772.0f, -99.0f));

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void LongPlatformBackPixel::Update()
	{
		GameObject::Update();

	}

	void LongPlatformBackPixel::Render(HDC hdc)
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

	void LongPlatformBackPixel::Release()
	{
		GameObject::Release();
	}

	void LongPlatformBackPixel::OnCollisionEnter(Collider* other)
	{
		


	}

	void LongPlatformBackPixel::OnCollisionStay(Collider* other)
	{
		int a = 0;

		
		Player* mPlayer = Player::GetInstance();
		Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
		Vector2 pos = tr->GetPos(); // ㅇ브젝트
		//playerPos = Camera::CalculatePos(playerPos);
		RigidBody* rb = mPlayer->GetComponent<RigidBody>();

		COLORREF color = mImage->GetPixel(pos.x - playerPos.x + (mCollider->GetSize().x / 2), pos.y - playerPos.y);
		if (color == RGB(255, 0, 0))
		{
			playerPos.y -= 1.0f;
			mPlayer->GetComponent<Transform>()->SetPos(playerPos);

			rb->SetGround(true);
			mPlayer->SetPlayerState(Player::ePlayerState::Idle);
		}

		/*
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mPlayer = Player::GetInstance();
			Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
			COLORREF color = mImage->GetPixel(playerPos.x, playerPos.y);
			RigidBody* rb = mPlayer->GetComponent<RigidBody>();
			Vector2 dir = rb->GetVelocity().Normalize();	// 플레이어 벡터 방향

			if (color == RGB(255, 0, 0))
			{
				// to up
				if (0.0f > dir.y && dir.y >= -1.0f)
				{
					playerPos.y += 1.0f;
				}

				// to down
				if (0.0f < dir.y && dir.y <= 1.0f)
				{
					playerPos.y -= 1.0f;
				}
				// to right
				if (0.0f < dir.x && dir.x <= 1.0f)
				{
					playerPos.x -= 1.0f;
				}

				// to left
				if (0.0f > dir.x && dir.x >= -1.0f)
				{
					playerPos.x += 1.0f;
				}
			}

		}
		*/
	}

	void LongPlatformBackPixel::OnCollisionExit(Collider* other)
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