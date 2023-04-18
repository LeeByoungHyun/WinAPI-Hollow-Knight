#include "Wave01.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaRigidBody.h"
#include "yaImage.h"
#include "yaResourceManager.h"
#include "yaCamera.h"

#include "FalseKnight.h"
#include "yaPlayer.h"

namespace ya
{
	Wave01::Wave01()
	{

	}

	Wave01::~Wave01()
	{

	}

	void Wave01::Initialize()
	{
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mRigidbody = AddComponent<RigidBody>();

		mImageL = ResourceManager::Load<Image>(L"Wave01", L"..\\Resources\\False Knight\\FalseKnight_Attack Wave\\FalseWave01.bmp");
		mImageR = ResourceManager::Load<Image>(L"Wave01", L"..\\Resources\\False Knight\\FalseKnight_Attack Wave\\FalseWave01r.bmp");

		mState = eWave01State::Active;
		mRigidbody->SetGround(true);

		GameObject::Initialize();
	}

	void Wave01::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::Wave01::eWave01State::Disable:
			disable();
			break;

		case ya::Wave01::eWave01State::Active:
			active();
			break;

		default:
			break;
		}
	}

	void Wave01::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// 카메라 위치에 맞추어 좌표 계산
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);

		if (mDirection == eDirection::Left)
		{
			pos.x -= mImageL->GetWidth() / 2;
			pos.y -= mImageL->GetHeight();
			TransparentBlt(hdc, pos.x, pos.y, mImageL->GetWidth(), mImageL->GetHeight()
				, mImageL->GetHdc(), 0, 0, mImageL->GetWidth(), mImageL->GetHeight(), RGB(255, 0, 255));
		}
		else if (mDirection == eDirection::Right)
		{
			pos.x -= mImageR->GetWidth() / 2;
			pos.y -= mImageR->GetHeight();
			TransparentBlt(hdc, pos.x, pos.y, mImageR->GetWidth(), mImageR->GetHeight()
				, mImageR->GetHdc(), 0, 0, mImageR->GetWidth(), mImageR->GetHeight(), RGB(255, 0, 255));
		}
	}

	void Wave01::Release()
	{
		GameObject::Release();
	}

	void Wave01::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Wave01::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Wave01::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Wave01::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			mCollider->SetSize(Vector2::Zero);
			mCollider->SetActive(false);
			this->SetState(eState::Pause);
		}
	}

	void Wave01::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;

			// FalseKnight 위치에 생성
			//Vector2 pos = FalseKnight::GetInstance()->GetComponent<Transform>()->GetPos();
			//pos.y -= 40.0f;
			//tr->SetPos(pos);

			mCollider->SetActive(true);
			mCollider->SetSize(Vector2(26.0f, 27.0f));

			if (FalseKnight::GetInstance()->GetDirection() == FalseKnight::eDirection::Left)
			{
				mDirection = eDirection::Left;
				mCollider->SetCenter(Vector2(0.0f, 0.0f));
			}
			
			else if (FalseKnight::GetInstance()->GetDirection() == FalseKnight::eDirection::Right)
			{
				mDirection = eDirection::Right;
				mCollider->SetCenter(Vector2(0.0f, 0.0f));
			}
		}

		Vector2 speed = Vector2::Zero;
		if (mDirection == eDirection::Left)
		{
			speed.x -= 100.0f * Time::DeltaTime();
			if (speed.x <= -700.0f)
				speed.x = -700.0f;
		}
		else if (mDirection == eDirection::Right)
		{
			speed += 100.0f * Time::DeltaTime();
			if (speed.x >= 700.0f)
				speed.x = 700.0f;
		}

		mRigidbody->SetVelocity(speed);

	}
}