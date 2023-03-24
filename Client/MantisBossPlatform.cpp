#include "MantisBossPlatform.h"
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
	MantisBossPlatform::MantisBossPlatform()
	{

	}

	MantisBossPlatform::~MantisBossPlatform()
	{

	}

	void MantisBossPlatform::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"MantisBossPlatform", L"..\\Resources\\GodHome\\MantisBossPlatform.bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1182.0f, 99.0f));
		mCollider->SetCenter(Vector2(-591.0f, -99.0f));

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void MantisBossPlatform::Update()
	{
		GameObject::Update();
	}

	void MantisBossPlatform::Render(HDC hdc)
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

	void MantisBossPlatform::Release()
	{
		GameObject::Release();
	}

	void MantisBossPlatform::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = Player::GetInstance();
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();

			Collider* playerCol = mplayer->GetComponent<Collider>();
			Vector2 playerColPos = playerCol->GetPos();
			Collider* objectCol = this->GetComponent<Collider>();
			Vector2 objectColPos = objectCol->GetPos();

			Transform* playerTr = mplayer->GetComponent<Transform>();
			Transform* objectTr = this->GetComponent<Transform>();
			Vector2 playerPos = playerTr->GetPos();
			Vector2 objectPos = objectTr->GetPos();

			playerPos.y = objectColPos.y + 1.0f;
			playerTr->SetPos(playerPos);
		}
	}

	void MantisBossPlatform::OnCollisionStay(Collider* other)
	{

	}

	void MantisBossPlatform::OnCollisionExit(Collider* other)
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