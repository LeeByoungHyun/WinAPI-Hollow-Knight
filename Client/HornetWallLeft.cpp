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
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = Player::GetInstance();
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();

			Collider* playerCol = mplayer->GetComponent<Collider>();
			Collider* objectCol = this->GetComponent<Collider>();

			Transform* playerTr = mplayer->GetComponent<Transform>();
			Transform* objectTr = this->GetComponent<Transform>();

			Vector2 playerPos = playerTr->GetPos();
			Vector2 objectPos = objectTr->GetPos();

			Vector2 dir = mplayer->GetComponent<RigidBody>()->GetVelocity().Normalize();	// 플레이어 벡터 방향
			if (0 > dir.x && dir.x >= -1)
			{
				playerPos.x = objectPos.x + playerCol->GetSize().x + 10.0f;
				playerTr->SetPos(playerPos);
			}

		}
		if (otherType == eLayerType::Hornet)
		{
			Hornet* mHornet = Hornet::GetInstance();
			if (mHornet == nullptr)
				return;

			RigidBody* rb = mHornet->GetComponent<RigidBody>();

			Collider* hornetCol = mHornet->GetComponent<Collider>();
			Collider* objectCol = this->GetComponent<Collider>();

			Transform* hornetTr = mHornet->GetComponent<Transform>();
			Transform* objectTr = this->GetComponent<Transform>();

			Vector2 hornetPos = hornetTr->GetPos();
			Vector2 objectPos = objectTr->GetPos();

			Vector2 dir = mHornet->GetComponent<RigidBody>()->GetVelocity().Normalize();	// 플레이어 벡터 방향
			if (mHornet->GetHornetDirection() == eDirection::Left)
			{
				hornetPos.x = objectPos.x + hornetCol->GetSize().x / 2 + 10.0f;
				hornetTr->SetPos(hornetPos);
			}

		}
	}

	void HornetWallLeft::OnCollisionExit(Collider* other)
	{

	}
}