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
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Run\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Run\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump(Anticipate)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump(Anticipate)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Land\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Land\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate A)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate A)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate G)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate G)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Recover)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Recover)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Anticipate)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Anticipate)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Recover)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Recover)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Wall Impact\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Wall Impact\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Anticipate)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Anticipate)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Recover)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Recover)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Anticipate)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Anticipate)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Recover)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Recover)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Anticipate)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Anticipate)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Anticipate)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Anticipate)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(End)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(End)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Stance)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Stance)\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade\\right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade(Anticipate)\\left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade(Anticipate)\\right", Vector2::Zero, 0.08f);

		mRigidBody->SetMass(1.0f);
		mRigidBody->SetGravity(Vector2(0.0f, 2000.0f));
		mState = eHornetState::Idle;

		GameObject::Initialize();
	}

	void Hornet::Update()
	{

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
			mCollider->SetCenter(Vector2(-30.0f, -200.0f));
			mCollider->SetSize(Vector2(60.0f, 200.0f));

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Hornet_Idleleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Hornet_Idleright", true);

			mRigidBody->SetVelocity(Vector2::Zero);
			idleFlag = true;
		}

		// 중립상태에서 일정시간이 지나면 랜덤하게 패턴 실행

	}

	void Hornet::run()
	{
		if (runFlag == false)
		{
			mCollider->SetCenter(Vector2(-30.0f, -200.0f));
			mCollider->SetSize(Vector2(60.0f, 200.0f));

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"Hornet_Runleft", true);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"Hornet_Runright", true);

			mRigidBody->SetVelocity(Vector2::Zero);
			runFlag = true;
		}
	}
	void Hornet::JumpAnticipate()
	{
	}
	void Hornet::jump()
	{
	}
	void Hornet::land()
	{
	}
	void Hornet::gDashAnticipate()
	{
	}
	void Hornet::gDash()
	{
	}
	void Hornet::gDashRecover()
	{
	}
	void Hornet::aDashAnticipate()
	{
	}
	void Hornet::aDash()
	{
	}
	void Hornet::aDashRecover()
	{
	}
	void Hornet::sphereAnticipateG()
	{
	}
	void Hornet::sphereAnticipateA()
	{
	}
	void Hornet::sphere()
	{
	}
	void Hornet::sphereRecover()
	{
	}
	void Hornet::throwNeedleAnticipate()
	{
	}
	void Hornet::throwNeedle()
	{
	}
	void Hornet::throwNeedleRecover()
	{
	}
	void Hornet::counterAnticipate()
	{
	}
	void Hornet::counterStance()
	{
	}
	void Hornet::counterEnd()
	{
	}
	void Hornet::counterAttackAnticipate()
	{
	}
	void Hornet::counterAttack()
	{
	}
	void Hornet::counterAttackRecover()
	{
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
