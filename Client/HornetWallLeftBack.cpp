#include "HornetWallLeftBack.h"
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
#include "Application.h"

#include "yaPlayer.h"
#include "Hornet.h"

namespace ya
{


	HornetWallLeftBack::HornetWallLeftBack()
	{

	}

	HornetWallLeftBack::~HornetWallLeftBack()
	{

	}

	void HornetWallLeftBack::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"HornetWallLeftBack", L"..\\Resources\\GodHome\\LeftWallBackPixel(Hornet).bmp");

		//mCollider = AddComponent<Collider>();

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void HornetWallLeftBack::Update()
	{
		GameObject::Update();

		Vector2 playerPos = Player::GetInstance()->GetComponent<Transform>()->GetPos();
		Vector2 hornetPos = Hornet::GetInstance()->GetComponent<Transform>()->GetPos();

		Vector2 playerSize = Player::GetInstance()->GetComponent<Collider>()->GetSize();
		Vector2 hornetSize = Hornet::GetInstance()->GetComponent<Collider>()->GetSize();

		playerPos = Vector2(playerPos.x - (playerSize.x / 2), playerPos.y);
		//playerPos = Camera::CalculatePos(playerPos);
		//playerPos.x -= mImage->GetWidth() / 2;
		//playerPos.y -= mImage->GetHeight();

		COLORREF playerColor = mImage->GetPixel(playerPos.x, playerPos.y);

		if (playerColor == RGB(255, 0, 0))
		{
			playerPos.x += 1.0f;
			Player::GetInstance()->GetComponent<Transform>()->SetPos(playerPos);
		}
		if (mImage->GetPixel(hornetPos.x - (hornetSize.x / 2), hornetPos.y) == RGB(255, 0, 0))
		{
			hornetPos.x += 1.0f;
			Hornet::GetInstance()->GetComponent<Transform>()->SetPos(hornetPos);
		}
	}

	void HornetWallLeftBack::Render(HDC hdc)
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

	void HornetWallLeftBack::Release()
	{
		GameObject::Release();
	}

	void HornetWallLeftBack::OnCollisionEnter(Collider* other)
	{

	}

	void HornetWallLeftBack::OnCollisionStay(Collider* other)
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

	void HornetWallLeftBack::OnCollisionExit(Collider* other)
	{

	}
}