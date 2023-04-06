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

#include "yaPlayer.h"

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
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Run\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Run\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Land\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Land\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate A)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate A)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate G)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate G)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Wall Impact\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Wall Impact\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(End)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(End)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Stance)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Stance)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade(Anticipate)\\right", Vector2::Zero, 0.1f);

		mRigidBody->SetMass(1.0f);
		mRigidBody->SetGravity(Vector2(0.0f, 2000.0f));
		mState = eHornetState::Idle;

		GameObject::Initialize();
	}

	void Hornet::Update()
	{
		// 테스트용
		if (Input::GetKeyDown(eKeyCode::O))
		{
			mState = eHornetState::CounterAttackRecover;

			idleFlag = false;
			runFlag = false;
			jumpAnticipateFlag = false;
			jumpFlag = false;
			landFlag = false;
			gDashAnticipateFlag = false;
			gDashFlag = false;
			gDashRecoverFlag = false;
			aDashAnticipateFlag = false;
			aDashFlag = false;
			aDashRecoverFlag = false;
			sphereAnticipateGFlag = false;
			sphereAnticipateAFlag = false;
			sphereFlag = false;
			sphereRecoverFlag = false;
			throwNeedleAnticipateFlag = false;
			throwNeedleFlag = false;
			throwNeedleRecoverFlag = false;
			counterAnticipateFlag = false;
			counterStanceFlag = false;
			counterEndFlag = false;
			counterAttackAnticipateFlag = false;
			counterAttackFlag = false;
			counterAttackRecoverFlag = false;
			barbThrowAnticipateFlag = false;
			barbThrowFlag = false;
			barbThrowRecoverFlag = false;
			stunAirFlag = false;
			stunFlag = false;
			woundedFlag = false;
			flashFlag = false;
		}

		// 테스트용
		Vector2 playerPos = Player::GetInstance()->GetPos();
		if (playerPos.x > tr->GetPos().x)
			mDirection = eDirection::Right;
		else
			mDirection = eDirection::Left;

		/*
		// 플레이어 위치에 따라 방향 전환
		if (mState == eFalseKnightState::Idle)
		{
			Vector2 playerPos = Player::GetInstance()->GetPos();
			if (playerPos.x > tr->GetPos().x)
				mDirection = eDirection::Right;
			else
				mDirection = eDirection::Left;
		}
		*/

		// FSM
		switch (mState)
		{
		case ya::Hornet::eHornetState::Idle:
			idle();
			break;

		case ya::Hornet::eHornetState::Run:
			run();
			break;

		case ya::Hornet::eHornetState::JumpAnticipate:
			JumpAnticipate();
			break;

		case ya::Hornet::eHornetState::Jump:
			jump();
			break;

		case ya::Hornet::eHornetState::Land:
			land();
			break;

		case ya::Hornet::eHornetState::GDashAnticipate:
			gDashAnticipate();
			break;

		case ya::Hornet::eHornetState::GDash:
			gDash();
			break;

		case ya::Hornet::eHornetState::GDashRecover:
			gDashRecover();
			break;

		case ya::Hornet::eHornetState::ADashAnticipate:
			aDashAnticipate();
			break;

		case ya::Hornet::eHornetState::ADash:
			aDash();
			break;

		case ya::Hornet::eHornetState::ADashRecover:
			aDashRecover();
			break;

		case ya::Hornet::eHornetState::SphereAnticipateG:
			sphereAnticipateG();
			break;

		case ya::Hornet::eHornetState::SphereAnticipateA:
			sphereAnticipateA();
			break;

		case ya::Hornet::eHornetState::Sphere:
			sphere();
			break;

		case ya::Hornet::eHornetState::SphereRecover:
			sphereRecover();
			break;

		case ya::Hornet::eHornetState::ThrowNeedleAnticipate:
			throwNeedleAnticipate();
			break;

		case ya::Hornet::eHornetState::ThrowNeedle:
			throwNeedle();
			break;

		case ya::Hornet::eHornetState::ThrowNeedleRecover:
			throwNeedleRecover();
			break;

		case ya::Hornet::eHornetState::CounterAnticipate:
			counterAnticipate();
			break;

		case ya::Hornet::eHornetState::CounterStance:
			counterStance();
			break;

		case ya::Hornet::eHornetState::CounterEnd:
			counterEnd();
			break;

		case ya::Hornet::eHornetState::CounterAttackAnticipate:
			counterAttackAnticipate();
			break;

		case ya::Hornet::eHornetState::CounterAttack:
			counterAttack();
			break;

		case ya::Hornet::eHornetState::CounterAttackRecover:
			counterAttackRecover();
			break;

		case ya::Hornet::eHornetState::BarbThrowAnticipate:
			barbThrowAnticipate();
			break;

		case ya::Hornet::eHornetState::BarbThrow:
			barbThrow();
			break;

		case ya::Hornet::eHornetState::BarbThrowRecover:
			barbThrowRecover();
			break;

		case ya::Hornet::eHornetState::StunAir:
			stunAir();
			break;

		case ya::Hornet::eHornetState::Stun:
			stun();
			break;

		case ya::Hornet::eHornetState::Wounded:
			wounded();
			break;

		case ya::Hornet::eHornetState::Flash:
			flash();
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

		eLayerType otherType = other->GetOwner()->GetType();	// 충돌한 객체의 타입
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
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Idleleft", true);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Idleright", true);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			idleFlag = true;
		}

		// 중립상태에서 일정시간이 지나면 랜덤하게 패턴 실행

	}

	void Hornet::run()
	{
		if (runFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Runleft", true);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Runright", true);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			runFlag = true;
		}
	}
	void Hornet::JumpAnticipate()
	{
		if (jumpAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -140.0f));
				mCollider->SetSize(Vector2(60.0f, 140.0f));
				mAnimator->Play(L"Hornet_Jump(Anticipate)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -140.0f));
				mCollider->SetSize(Vector2(60.0f, 140.0f));
				mAnimator->Play(L"Hornet_Jump(Anticipate)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			jumpAnticipateFlag = true;
		}
	}

	void Hornet::jump()
	{
		if (jumpFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -180.0f));
				mCollider->SetSize(Vector2(60.0f, 150.0f));
				mAnimator->Play(L"Hornet_Jumpleft", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -180.0f));
				mCollider->SetSize(Vector2(60.0f, 150.0f));
				mAnimator->Play(L"Hornet_Jumpright", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			jumpFlag = true;
		}
	}

	void Hornet::land()
	{
		if (landFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Landleft", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Landright", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			landFlag = true;
		}
	}

	void Hornet::gDashAnticipate()
	{
		if (gDashAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dash(Anticipate)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dash(Anticipate)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			gDashAnticipateFlag = true;
		}
	}

	void Hornet::gDash()
	{
		if (gDashFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(0.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dashleft", false);
			}
				
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-60.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dashright", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			gDashFlag = true;
		}
	}

	void Hornet::gDashRecover()
	{
		if (gDashRecoverFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(0.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dash(Recover)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-60.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dash(Recover)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			gDashRecoverFlag = true;
		}
	}

	void Hornet::aDashAnticipate()
	{
		if (aDashAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -120.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dash(Anticipate)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -120.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dash(Anticipate)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			aDashAnticipateFlag = true;
		}
	}

	void Hornet::aDash()
	{
		if (aDashFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(0.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dashleft", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-60.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dashright", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			aDashFlag = true;
		}
	}

	void Hornet::aDashRecover()
	{
		if (aDashRecoverFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -130.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dash(Recover)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -130.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dash(Recover)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			aDashRecoverFlag = true;
		}
	}

	void Hornet::sphereAnticipateG()
	{
		if (sphereAnticipateGFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -130.0f));
				mCollider->SetSize(Vector2(60.0f, 130.0f));
				mAnimator->Play(L"Hornet_Sphere(Anticipate G)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -130.0f));
				mCollider->SetSize(Vector2(60.0f, 130.0f));
				mAnimator->Play(L"Hornet_Sphere(Anticipate G)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			sphereAnticipateGFlag = true;
		}
	}

	void Hornet::sphereAnticipateA()
	{
		if (sphereAnticipateAFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-80.0f, -110.0f));
				mCollider->SetSize(Vector2(100.0f, 80.0f));
				mAnimator->Play(L"Hornet_Sphere(Anticipate A)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -110.0f));
				mCollider->SetSize(Vector2(100.0f, 80.0f));
				mAnimator->Play(L"Hornet_Sphere(Anticipate A)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			sphereAnticipateAFlag = true;
		}
	}

	void Hornet::sphere()
	{
		if (sphereFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -130.0f));
				mCollider->SetSize(Vector2(75.0f, 100.0f));
				mAnimator->Play(L"Hornet_Sphereleft", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-50.0f, -130.0f));
				mCollider->SetSize(Vector2(75.0f, 100.0f));
				mAnimator->Play(L"Hornet_Sphereright", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			sphereFlag = true;
		}
	}

	void Hornet::sphereRecover()
	{
		if (sphereRecoverFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -130.0f));
				mCollider->SetSize(Vector2(75.0f, 100.0f));
				mAnimator->Play(L"Hornet_Sphere(Recover)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-50.0f, -130.0f));
				mCollider->SetSize(Vector2(75.0f, 100.0f));
				mAnimator->Play(L"Hornet_Sphere(Recover)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			sphereRecoverFlag = true;
		}
	}

	void Hornet::throwNeedleAnticipate()
	{
		if (throwNeedleAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-20.0f, -140.0f));
				mCollider->SetSize(Vector2(80.0f, 140.0f));
				mAnimator->Play(L"Hornet_Throw(Anticipate)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-60.0f, -140.0f));
				mCollider->SetSize(Vector2(80.0f, 140.0f));
				mAnimator->Play(L"Hornet_Throw(Anticipate)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			throwNeedleAnticipateFlag = true;
		}
	}

	void Hornet::throwNeedle()
	{
		if (throwNeedleFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-65.0f, -100.0f));
				mCollider->SetSize(Vector2(130.0f, 100.0f));
				mAnimator->Play(L"Hornet_Throwleft", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-65.0f, -100.0f));
				mCollider->SetSize(Vector2(130.0f, 100.0f));
				mAnimator->Play(L"Hornet_Throwright", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			throwNeedleFlag = true;
		}
	}

	void Hornet::throwNeedleRecover()
	{
		if (throwNeedleRecoverFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-65.0f, -100.0f));
				mCollider->SetSize(Vector2(130.0f, 100.0f));
				mAnimator->Play(L"Hornet_Throw(Recover)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-65.0f, -100.0f));
				mCollider->SetSize(Vector2(130.0f, 100.0f));
				mAnimator->Play(L"Hornet_Throw(Recover)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			throwNeedleRecoverFlag = true;
		}
	}

	void Hornet::counterAnticipate()
	{
		if (counterAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-92.5f, -120.0f));
				mCollider->SetSize(Vector2(185.0f, 120.0f));
				mAnimator->Play(L"Hornet_Counter(Anticipate)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-92.5f, -120.0f));
				mCollider->SetSize(Vector2(185.0f, 120.0f));
				mAnimator->Play(L"Hornet_Counter(Anticipate)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			counterAnticipateFlag = true;
		}
	}

	void Hornet::counterStance()
	{
		if (counterStanceFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-92.5f, -120.0f));
				mCollider->SetSize(Vector2(185.0f, 120.0f));
				mAnimator->Play(L"Hornet_Counter(Stance)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-92.5f, -120.0f));
				mCollider->SetSize(Vector2(185.0f, 120.0f));
				mAnimator->Play(L"Hornet_Counter(Stance)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			counterStanceFlag = true;
		}
	}

	void Hornet::counterEnd()
	{
		if (counterEndFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Counter(End)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Counter(End)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			counterEndFlag = true;
		}
	}

	void Hornet::counterAttackAnticipate()
	{
		if (counterAttackAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-40.0f, -100.0f));
				mCollider->SetSize(Vector2(140.0f, 100.0f));
				mAnimator->Play(L"Hornet_Counter Attack(Anticipate)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-100.0f, -100.0f));
				mCollider->SetSize(Vector2(140.0f, 100.0f));
				mAnimator->Play(L"Hornet_Counter Attack(Anticipate)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			counterAttackAnticipateFlag = true;
		}
	}

	void Hornet::counterAttack()
	{
		if (counterAttackFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-20.0f, -90.0f));
				mCollider->SetSize(Vector2(130.0f, 90.0f));
				mAnimator->Play(L"Hornet_Counter Attackleft", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-110.0f, -90.0f));
				mCollider->SetSize(Vector2(130.0f, 90.0f));
				mAnimator->Play(L"Hornet_Counter Attackright", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			counterAttackFlag = true;
		}
	}

	void Hornet::counterAttackRecover()
	{
		if (counterAttackRecoverFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-100.0f, -150.0f));
				mCollider->SetSize(Vector2(80.0f, 150.0f));
				mAnimator->Play(L"Hornet_Counter Attack(Recover)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(20.0f, -150.0f));
				mCollider->SetSize(Vector2(80.0f, 150.0f));
				mAnimator->Play(L"Hornet_Counter Attack(Recover)right", false);
			}

			mRigidBody->SetVelocity(Vector2::Zero);
			counterAttackRecoverFlag = true;
		}
	}

	void Hornet::barbThrowAnticipate()
	{

	}

	void Hornet::barbThrow()
	{

	}

	void Hornet::barbThrowRecover()
	{

	}

	void Hornet::stunAir()
	{

	}

	void Hornet::stun()
	{

	}

	void Hornet::wounded()
	{

	}

	void Hornet::flash()
	{

	}
}
