#include "HornetWallLeft.h"
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

namespace ya
{
	HornetWallLeft::HornetWallLeft()
	{

	}

	HornetWallLeft::~HornetWallLeft()
	{

	}

	void HornetWallLeft::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"HornetWallLeft", L"..\\Resources\\GodHome\\LeftWall(Hornet).bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(81.0f, 1089.0f));
		mCollider->SetCenter(Vector2(-40.5f, -1089.0f));

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void HornetWallLeft::Update()
	{
		GameObject::Update();
	}

	void HornetWallLeft::Render(HDC hdc)
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

	void HornetWallLeft::Release()
	{
		GameObject::Release();
	}

	void HornetWallLeft::OnCollisionEnter(Collider* other)
	{

	}

	void HornetWallLeft::OnCollisionStay(Collider* other)
	{
		/*
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mPlayer = Player::GetInstance();
			Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
			Vector2 pos = tr->GetPos(); // ㅇ브젝트
			RigidBody* rb = mPlayer->GetComponent<RigidBody>();

			COLORREF color = mImage->GetPixel(pos.x - playerPos.x + (mCollider->GetSize().x / 2), pos.y - playerPos.y);
			if (color == RGB(255, 0, 0))
			{
				playerPos.y -= 1.0f;
				mPlayer->GetComponent<Transform>()->SetPos(playerPos);

				rb->SetGround(true);
				mPlayer->SetPlayerState(Player::ePlayerState::Idle);
			}
		}

		if (otherType == eLayerType::Monster)
		{
			Hornet* mHornet = Hornet::GetInstance();
			Vector2 hornetPos = mHornet->GetComponent<Transform>()->GetPos();
			Vector2 pos = tr->GetPos(); 
			RigidBody* rb = mHornet->GetComponent<RigidBody>();

			COLORREF color = mImage->GetPixel(pos.x - hornetPos.x + (mCollider->GetSize().x / 2), pos.y - hornetPos.y);
			if (color == RGB(255, 0, 0))
			{
				hornetPos.y -= 1.0f;
				mHornet->GetComponent<Transform>()->SetPos(hornetPos);
			}
		}
		*/
	}

	void HornetWallLeft::OnCollisionExit(Collider* other)
	{

	}
}