#include "SphereBall.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaRigidBody.h"

#include "Hornet.h"
#include "yaPlayer.h"

namespace ya
{
	Vector2 SphereBallPlayerPos;
	Vector2 SphereBallPlayerDir;

	SphereBall::SphereBall()
	{
		tr = AddComponent<Transform>();
	}

	SphereBall::~SphereBall()
	{

	}

	void SphereBall::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Ball)\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Hornet_Sphere(Ball)neutral") = std::bind(&SphereBall::ballCompleteEvent, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetActive(false);
		mCollider->SetSize(Vector2::Zero);

		GameObject::Initialize();
	}

	void SphereBall::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::SphereBall::eSphereBallState::Disable:
			disable();
			break;

		case ya::SphereBall::eSphereBallState::Active:
			active();
			break;

		case ya::SphereBall::eSphereBallState::Ball:
			ball();
			break;

		default:
			break;
		}

	}

	void SphereBall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SphereBall::Release()
	{
		GameObject::Release();
	}

	void SphereBall::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void SphereBall::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void SphereBall::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void SphereBall::disable()
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

	void SphereBall::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;
			this->SetState(eState::Active);

			// Hornet위치에 생성
			Vector2 pos = Hornet::GetInstance()->GetComponent<Transform>()->GetPos();	
			pos.y += 100.0f;
			tr->SetPos(pos);

			mState = eSphereBallState::Ball;
		}
	}

	void SphereBall::ball()
	{
		if (ballFlag == false)
		{
			mAnimator->Play(L"Hornet_Sphere(Ball)neutral", false);
			mCollider->SetSize(Vector2(370.0f, 370.0f));
			mCollider->SetCenter(Vector2(-185.0f, -390.0f));
			mCollider->SetActive(true);

			ballFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.594f)
		{
			mTime = 0.0f;
			mState = eSphereBallState::Disable;
			ballFlag = false;
		}
	}

	void SphereBall::ballCompleteEvent()
	{
		//mState = eSphereBallState::Disable;
		//ballFlag = false;
	}
}