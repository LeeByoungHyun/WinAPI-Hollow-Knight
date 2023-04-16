#include "HornetWallRight.h"
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
	HornetWallRight::HornetWallRight()
	{

	}

	HornetWallRight::~HornetWallRight()
	{

	}

	void HornetWallRight::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"HornetWallRight", L"..\\Resources\\GodHome\\RightWall(Hornet).bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(81.0f, 1089.0f));
		mCollider->SetCenter(Vector2(-40.5f, -1089.0f));

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void HornetWallRight::Update()
	{
		GameObject::Update();
	}

	void HornetWallRight::Render(HDC hdc)
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

	void HornetWallRight::Release()
	{
		GameObject::Release();
	}

	void HornetWallRight::OnCollisionEnter(Collider* other)
	{

	}

	void HornetWallRight::OnCollisionStay(Collider* other)
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
			if (0 < dir.x && dir.x <= 1)
			{
				playerPos.x = objectPos.x - playerCol->GetSize().x - 10.0f;
				playerTr->SetPos(playerPos);
			}

		}
		if (otherType == eLayerType::Monster)
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
			if (0 < dir.x && dir.x <= 1)
			{
				hornetPos.x = objectPos.x - hornetCol->GetSize().x - 10.0f;
				hornetTr->SetPos(hornetPos);
			}

		}
	}

	void HornetWallRight::OnCollisionExit(Collider* other)
	{

	}
}