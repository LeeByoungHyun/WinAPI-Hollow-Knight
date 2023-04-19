#include "Wave03.h"
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
	Wave03::Wave03()
	{

	}

	Wave03::~Wave03()
	{

	}

	void Wave03::Initialize()
	{
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mRigidbody = AddComponent<RigidBody>();

		mImageL = ResourceManager::Load<Image>(L"Wave03", L"..\\Resources\\False Knight\\FalseKnight_Attack Wave\\FalseWave03.bmp");
		mImageR = ResourceManager::Load<Image>(L"Wave03", L"..\\Resources\\False Knight\\FalseKnight_Attack Wave\\FalseWave03r.bmp");

		mState = eWave03State::Disable;
		mRigidbody->SetGround(true);

		GameObject::Initialize();
	}

	void Wave03::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::Wave03::eWave03State::Disable:
			disable();
			break;

		case ya::Wave03::eWave03State::Active:
			active();
			break;

		default:
			break;
		}
	}

	void Wave03::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// active state에서만 render
		if (mState == eWave03State::Active)
		{
			// 카메라 위치에 맞추어 좌표 계산
			//tr = GetComponent<Transform>();
			Vector2 pos = Camera::CalculatePos(mPos);

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
	}

	void Wave03::Release()
	{
		GameObject::Release();
	}

	void Wave03::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		if (other->GetOwner()->GetType() == eLayerType::Wall)
			mState = eWave03State::Disable;
	}

	void Wave03::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Wave03::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Wave03::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			speed.x = 0.0f;
			mCollider->SetSize(Vector2::Zero);
			mCollider->SetActive(false);
			mRigidbody->SetVelocity(Vector2::Zero);
			//this->SetState(eState::Pause);
		}
	}

	void Wave03::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;

			// 생성위치
			//Vector2 pos = FalseKnight::GetInstance()->GetComponent<Transform>()->GetPos();
			//tr->SetPos(pos);
			tr->SetPos(mPos);
			mCollider->SetActive(true);
			mCollider->SetSize(Vector2(43.0f, 104.0f));
			mCollider->SetCenter(Vector2(-21.0f, -104.0f));
			mRigidbody->SetGround(true);

			if (FalseKnight::GetInstance()->GetDirection() == FalseKnight::eDirection::Left)
			{
				mDirection = eDirection::Left;
			}

			else if (FalseKnight::GetInstance()->GetDirection() == FalseKnight::eDirection::Right)
			{
				mDirection = eDirection::Right;
			}
		}

		Vector2 pos = mPos;
		if (mDirection == eDirection::Left)
		{
			speed.x -= FALSEWAVESPEED * Time::DeltaTime();
			if (speed.x <= -FALSEWAVESPEED)
				speed.x = -FALSEWAVESPEED;
			pos.x += speed.x * Time::DeltaTime();
		}
		else if (mDirection == eDirection::Right)
		{
			speed += FALSEWAVESPEED * Time::DeltaTime();
			if (speed.x >= FALSEWAVESPEED)
				speed.x = FALSEWAVESPEED;
			pos.x += speed.x * Time::DeltaTime();
		}
		tr->SetPos(pos);
		mPos = pos;
	}
}