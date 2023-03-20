#include "LongFlatform.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidBody.h"

#include "yaPlayer.h"

namespace ya
{
	LongFlatform::LongFlatform()
	{

	}

	LongFlatform::~LongFlatform()
	{

	}

	void LongFlatform::Initialize()
	{
		//mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\room1.bmp");
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\GodHome\\Platform", Vector2::Zero, 1.0f);

		mAnimator->Play(L"GodHomePlatform", false);

		mCollider->SetSize(Vector2(1183.0f, 103.0f));
		mCollider->SetCenter(Vector2(-591.5f, -103.0f));

		GameObject::Initialize();
	}

	void LongFlatform::Update()
	{
		GameObject::Update();
	}

	void LongFlatform::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//BitBlt(hdc, tr->GetPos().x, tr->GetPos().y - 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void LongFlatform::Release()
	{
		GameObject::Release();

	}
	void LongFlatform::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();
			rb->SetGround(true);

			// 충돌한 콜라이더가 가속도로 인해 1프레임 사이에 콜라이더 안으로 들어갈 경우 콜라이더 위치 초기화
			Collider* playerCol = mplayer->GetComponent<Collider>();
			Vector2 playerPos = playerCol->GetPos();

			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 groundPos = groundCol->GetPos();

			float fLen = fabs(playerPos.y - groundPos.y);
			float fSize = (playerCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

			if (fLen < fSize)
			{
				Transform* playerTr = mplayer->GetComponent<Transform>();
				Transform* grTr = this->GetComponent<Transform>();

				Vector2 pPos = playerTr->GetPos();
				Vector2 grPos = grTr->GetPos();

				pPos -= (fSize - fLen) - 1.0f;
				playerTr->SetPos(pPos);
			}
		}
	}
	void LongFlatform::OnCollisionStay(Collider* other)
	{
		
	}
	void LongFlatform::OnCollisionExit(Collider* other)
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