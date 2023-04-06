#include "Hornet.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaRigidBody.h"
#include "yaCamera.h"
#include "yaSound.h"

namespace ya
{
	// 싱글톤 객체 초기화
	Hornet* Hornet::instance = nullptr;

	Hornet::Hornet()
	{
		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		curScene = SceneManager::GetActiveScene();
		mRigidBody = AddComponent<RigidBody>();
		mCollider = AddComponent<Collider>();
	}

	Hornet::~Hornet()
	{

	}

	void Hornet::Initialize()
	{
		// 애니메이션
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\right", Vector2::Zero, 0.1f);

		mCollider->SetName(L"PlayerCollider");
		mCollider->SetCenter(Vector2(-30.0f, -120.0f));
		mCollider->SetSize(Vector2(60.0f, 120.0f));

		mRigidBody->SetMass(1.0f);
		mRigidBody->SetGravity(Vector2(0.0f, 2000.0f));
		mState = eHornetState::Idle;

		GameObject::Initialize();
	}

	void Hornet::Update()
	{
		switch (mState)
		{
		case ya::Hornet::eHornetState::Idle:
			idle();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void Hornet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Hornet::Release()
	{
		GameObject::Release();
	}

	void Hornet::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		eLayerType otherType = other->GetOwner()->GetType();	// 플레이어와 충돌한 객체의 타입
		switch (otherType)
		{
			// 땅과 충돌할 경우
		case eLayerType::Ground:
			mRigidBody->SetGround(true);
			mRigidBody->SetVelocity(Vector2::Zero);
			break;
		}
	}

	void Hornet::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void Hornet::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void Hornet::idle()
	{
		if (idleFlag == false)
		{
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Hornet_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Hornet_Idleright", true);

			mRigidBody->SetVelocity(Vector2::Zero);
			idleFlag = true;
		}
	}
}
