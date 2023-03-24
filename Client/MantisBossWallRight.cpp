#include "MantisBossWallRight.h"
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
	MantisBossWallRight::MantisBossWallRight()
	{

	}

	MantisBossWallRight::~MantisBossWallRight()
	{

	}

	void MantisBossWallRight::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"MantisBossWallRight", L"..\\Resources\\GodHome\\MantisBossWallRight.bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(81.0f, 1089.0f));
		mCollider->SetCenter(Vector2(-40.5f, -1089.0f));

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void MantisBossWallRight::Update()
	{
		GameObject::Update();
	}

	void MantisBossWallRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// ī�޶� ��ġ�� ���߾� ��ǥ ���
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

	void MantisBossWallRight::Release()
	{
		GameObject::Release();
	}

	void MantisBossWallRight::OnCollisionEnter(Collider* other)
	{

	}

	void MantisBossWallRight::OnCollisionStay(Collider* other)
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

			Vector2 dir = mplayer->GetComponent<RigidBody>()->GetVelocity().Normalize();	// �÷��̾� ���� ����
			if (0 < dir.x && dir.x <= 1)
			{
				playerPos.x = objectPos.x - playerCol->GetSize().x - 10.0f;
				playerTr->SetPos(playerPos);
			}
			
		}
	}

	void MantisBossWallRight::OnCollisionExit(Collider* other)
	{

	}
}