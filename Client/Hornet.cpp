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
#include "Barb01.h"
#include "Barb02.h"
#include "Barb03.h"
#include "Barb04.h"
#include "SphereBall.h"
#include "HornetNeedle.h"
#include "CounterAttackCollider.h"

namespace ya
{
	// 싱글톤 객체 초기화
	Hornet* Hornet::instance = nullptr;
	Vector2 playerPos;
	Vector2 playerDir;
	const float WAITTIME = 0.5f;
	const float DASHSPEED = 1000.0f;
	const float EVADESPEED = 700.0f;
	const float RUNSPEED = 500.0f;

	Hornet::Hornet()
	{
		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		curScene = SceneManager::GetActiveScene();
		mRigidBody = AddComponent<RigidBody>();
		mCollider = AddComponent<Collider>();
		hp = 900;
		stunHp = 300;
		mTime = 0.0f;
	}

	Hornet::~Hornet()
	{

	}

	void Hornet::Initialize()
	{
		// 애니메이션
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Run\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Run\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Jump\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Land\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Land\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate A)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate A)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate G)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Anticipate G)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Recover)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Sphere(Recover)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Recover)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Throw(Recover)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Wall Impact\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Wall Impact\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Recover)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_A Dash(Recover)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Recover)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_G Dash(Recover)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Recover)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter Attack(Recover)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(End)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(End)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Stance)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Counter(Stance)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Evade(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Throw(Anticipate)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Throw(Anticipate)\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Throw\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Throw\\right", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Throw(Recover)\\left", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Throw(Recover)\\right", Vector2::Zero, 0.066f);

		mAnimator->GetCompleteEvent(L"Hornet_Jump(Anticipate)left") = std::bind(&Hornet::jumpAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Jump(Anticipate)right") = std::bind(&Hornet::jumpAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Jumpleft") = std::bind(&Hornet::jumpCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Jumpright") = std::bind(&Hornet::jumpCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Landleft") = std::bind(&Hornet::landCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Landright") = std::bind(&Hornet::landCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphere(Anticipate A)left") = std::bind(&Hornet::sphereAnticipateACompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphere(Anticipate A)right") = std::bind(&Hornet::sphereAnticipateACompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphere(Anticipate G)left") = std::bind(&Hornet::sphereAnticipateGCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphere(Anticipate G)right") = std::bind(&Hornet::sphereAnticipateGCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphereleft") = std::bind(&Hornet::sphereCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphereright") = std::bind(&Hornet::sphereCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphere(Recover)left") = std::bind(&Hornet::sphereRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Sphere(Recover)right") = std::bind(&Hornet::sphereRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_A Dash(Anticipate)left") = std::bind(&Hornet::aDashAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_A Dash(Anticipate)right") = std::bind(&Hornet::aDashAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_A Dash(Recover)left") = std::bind(&Hornet::aDashRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_A Dash(Recover)right") = std::bind(&Hornet::aDashRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_G Dash(Anticipate)left") = std::bind(&Hornet::gDashAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_G Dash(Anticipate)right") = std::bind(&Hornet::gDashAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_G Dash(Recover)left") = std::bind(&Hornet::gDashRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_G Dash(Recover)right") = std::bind(&Hornet::gDashRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Throw(Anticipate)left") = std::bind(&Hornet::throwNeedleAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Throw(Anticipate)right") = std::bind(&Hornet::throwNeedleAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Throwleft") = std::bind(&Hornet::throwNeedleCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Throwright") = std::bind(&Hornet::throwNeedleCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Throw(Recover)left") = std::bind(&Hornet::throwNeedleRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Throw(Recover)right") = std::bind(&Hornet::throwNeedleRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter(Anticipate)left") = std::bind(&Hornet::counterAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter(Anticipate)right") = std::bind(&Hornet::counterAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter(End)left") = std::bind(&Hornet::counterEndCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter(End)right") = std::bind(&Hornet::counterEndCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter Attack(Anticipate)left") = std::bind(&Hornet::counterAttackAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter Attack(Anticipate)right") = std::bind(&Hornet::counterAttackAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter Attackleft") = std::bind(&Hornet::counterAttackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter Attackright") = std::bind(&Hornet::counterAttackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter Attack(Recover)left") = std::bind(&Hornet::counterAttackRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Counter Attack(Recover)right") = std::bind(&Hornet::counterAttackRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Evade(Anticipate)left") = std::bind(&Hornet::evadeAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Evade(Anticipate)right") = std::bind(&Hornet::evadeAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Evadeleft") = std::bind(&Hornet::evadeCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Evaderight") = std::bind(&Hornet::evadeCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Runleft") = std::bind(&Hornet::runCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Runright") = std::bind(&Hornet::runCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Throw(Anticipate)left") = std::bind(&Hornet::barbThrowAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Throw(Anticipate)right") = std::bind(&Hornet::barbThrowAnticipateCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Throwleft") = std::bind(&Hornet::barbThrowCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Throwright") = std::bind(&Hornet::barbThrowCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Throw(Recover)left") = std::bind(&Hornet::barbThrowRecoverCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Throw(Recover)right") = std::bind(&Hornet::barbThrowRecoverCompleteEvent, this);

		mRigidBody->SetMass(1.0f);
		mRigidBody->SetGravity(Vector2(0.0f, 2000.0f));
		mState = eHornetState::Idle;

		// barb 미리 생성
		barb01 = object::Instantiate<Barb01>(eLayerType::Monster);
		barb02 = object::Instantiate<Barb02>(eLayerType::Monster);
		barb03 = object::Instantiate<Barb03>(eLayerType::Monster);
		barb04 = object::Instantiate<Barb04>(eLayerType::Monster);
		barb01->SetBarbState(Barb01::eBarbState::Disable);
		barb02->SetBarbState(Barb02::eBarbState::Disable);
		barb03->SetBarbState(Barb03::eBarbState::Disable);
		barb04->SetBarbState(Barb04::eBarbState::Disable);
		ball = object::Instantiate<SphereBall>(eLayerType::Monster);
		ball->SetShereBallState(SphereBall::eSphereBallState::Disable);
		needle = object::Instantiate<HornetNeedle>(eLayerType::Monster);
		needle->SetNeedeState(HornetNeedle::eHornetNeedleState::Disable);
		caCol = object::Instantiate<CounterAttackCollider>(eLayerType::Monster);

		GameObject::Initialize();
	}

	void Hornet::Update()
	{
		GameObject::Update();

		// 테스트용
		if (Input::GetKeyDown(eKeyCode::O))
		{
			mState = eHornetState::CounterAnticipate;

			initializeFlag();
		}

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
			jumpAnticipate();
			break;

		case ya::Hornet::eHornetState::Jump:
			jump();
			break;

		case ya::Hornet::eHornetState::Land:
			land();
			break;

		case ya::Hornet::eHornetState::EvadeAnticipate:
			evadeAnticipate();
			break;

		case ya::Hornet::eHornetState::Evade:
			evade();
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
		case eLayerType::Ground:	// 땅과 충돌할 경우
			if (mState == eHornetState::Idle)	
			{
				mRigidBody->SetGround(true);
				mRigidBody->SetVelocity(Vector2::Zero);

			}
			else if (mState == eHornetState::Jump 
				&& mRigidBody->GetVelocity().Normalize().y >= 0.0f)	
			{
				mState = eHornetState::Land;
				mRigidBody->SetGround(true);
				mRigidBody->SetVelocity(Vector2::Zero);
			}
			else if (mState == eHornetState::SphereRecover)	
			{
				mState = eHornetState::Land;
				mRigidBody->SetGround(true);
				mRigidBody->SetVelocity(Vector2::Zero);
			}
			else if (mState == eHornetState::ADash)	
			{
				mRigidBody->SetGround(true);
			}
			else if (mState == eHornetState::ADashRecover)
			{
				mState = eHornetState::Land;
				mRigidBody->SetGround(true);
				mRigidBody->SetVelocity(Vector2::Zero);
			}
			else if (mState == eHornetState::GDashRecover)
			{
				mRigidBody->SetGround(true);
			}
			break;

			// 플레이어의 공격일 경우
		case eLayerType::NeilEffect:
			if (mState == eHornetState::CounterStance)
			{
				mState = eHornetState::CounterAttackAnticipate;
				// 팅소리
			}
			else
			{
				hp -= Player::GetInstance()->GetNeilAtk();
				stunHp -= Player::GetInstance()->GetNeilAtk();
				//armorDamagedSound->Play(false);
			}
			break;
		case eLayerType::SpellEffect:
			if (mState == eHornetState::CounterStance)
			{
				mState = eHornetState::CounterAttackAnticipate;
				// 팅소리
			}
			else
			{
				hp -= Player::GetInstance()->GetSpellAtk();
				stunHp -= Player::GetInstance()->GetSpellAtk();
				//armorDamagedSound->Play(false);
			}
			break;

			// needle
		case eLayerType::Monster:
			float needleSpeed = needle->GetNeedleSpeed();
			if (mState == eHornetState::ThrowNeedle
				&& needleSpeed <= 0.0f)
			{
				if (mDirection == eDirection::Left)
				{
					Vector2 pos = tr->GetPos();
					pos.x -= 50.0f;
					tr->SetPos(pos);
				}
				else if (mDirection == eDirection::Right)
				{
					Vector2 pos = tr->GetPos();
					pos.x += 50.0f;
					tr->SetPos(pos);
				}

				mTime = 0.0f;
				mState = eHornetState::ThrowNeedleRecover;
				throwNeedleFlag = false;
				needleCatchFlag = false;
			}
			break;
		}
	}

	void Hornet::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);

		eLayerType otherType = other->GetOwner()->GetType();	// 충돌한 객체의 타입
		switch (otherType)
		{
			// 땅속에 있을 경우 땅위로 밀어냄
		case eLayerType::Ground:
			if (mState == eHornetState::Idle || mState == eHornetState::Land)
			{
				Vector2 pos = tr->GetPos();
				pos.y = other->GetPos().y - 1;
				tr->SetPos(pos);
				mRigidBody->SetVelocity(Vector2::Zero);
				mRigidBody->SetGround(true);
			}
			break;
		}
	}

	void Hornet::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void Hornet::idle()
	{
		if (idleFlag == false)
		{
			// 플레이어 방향으로 방향 전환
			Vector2 playerPos = Player::GetInstance()->GetPos();
			if (playerPos.x > tr->GetPos().x)
				mDirection = eDirection::Right;
			else
				mDirection = eDirection::Left;

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

			// 플레그 초기화
			initializeFlag();
		}

		// 중립상태에서 일정시간이 지나면 랜덤하게 패턴 실행
		// 1) run
		// 2) evade
		// 3) jump 
		// 4) throw
		// 5) dash 
		// 6) sphere
		// 7) burb 
		// 8) counter
		srand((unsigned int)time(NULL));
		idlePattern = rand() % 8;
		//idlePattern = 6;	// test
		mTime += Time::DeltaTime();
		if (mTime >= WAITTIME)
		{
			mTime = 0.0f;
			idleFlag = false;
			if (idlePattern == 0)
			{
				mState = eHornetState::Run;
			}
			else if (idlePattern == 1)
			{
				mState = eHornetState::EvadeAnticipate;
			}
			else if (idlePattern == 2)
			{
				mState = eHornetState::JumpAnticipate;
			}
			else if (idlePattern == 3)
			{
				mState = eHornetState::ThrowNeedleAnticipate;
			}
			else if (idlePattern == 4)
			{
				mState = eHornetState::GDashAnticipate;
			}
			else if (idlePattern == 5)
			{
				mState = eHornetState::SphereAnticipateG;
			}
			else if (idlePattern == 6)
			{
				// Barb가 scene에 남아있으면 continue
				if (barb01->GetBarbState() == Barb01::eBarbState::Disable 
					&& barb02->GetBarbState() == Barb02::eBarbState::Disable
					&& barb03->GetBarbState() == Barb03::eBarbState::Disable
					&& barb04->GetBarbState() == Barb04::eBarbState::Disable)
				{
					mState = eHornetState::BarbThrowAnticipate;
				}
			}
			else if (idlePattern == 7)
			{
				mState = eHornetState::CounterAnticipate;
			}
		}
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
			runFlag = true;
			idleFlag = false;
		}

		// 플레이어 방향으로
		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
			pos.x -= RUNSPEED * Time::DeltaTime();
		else if (mDirection == eDirection::Right)
			pos.x += RUNSPEED * Time::DeltaTime();
		tr->SetPos(pos);
	}
	void Hornet::jumpAnticipate()
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
			jumpAnticipateFlag = true;
			idleFlag = false;
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

			// 1) 그냥 점프
			// 2) 플레이어 방향으로 점프 후 Sphere
			// 3) 점프 후 플레이어 방향으로 대쉬(대각선)
			// 
			// 지금은 제자리 점프로 구현
			srand((unsigned int)time(NULL));
			jumpPattern = rand() % 3;
			//jumpPattern = 0;	// 테스트

			// 앞뒤로 점프거리 랜덤하게 
			// 지금은 테스트
			mRigidBody->SetVelocity(Vector2(0.0f, -1200.0f));
			mRigidBody->SetGround(false);

			jumpFlag = true;
			jumpAnticipateFlag = false;
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
			landFlag = true;
			jumpAnticipateFlag = false;
		}
	}

	void Hornet::evadeAnticipate()
	{
		if (evadeAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Evade(Anticipate)left", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Evade(Anticipate)right", false);
			}
			evadeAnticipateFlag = true;
			idleFlag = false;
		}
	}

	void Hornet::evade()
	{
		if (evadeFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Evadeleft", false);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Evaderight", false);
			}
			evadeFlag = true;
			evadeAnticipateFlag = false;
		}

		// 플레이어 반대방향으로 회피
		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
			pos.x += EVADESPEED * Time::DeltaTime();
		else if (mDirection == eDirection::Right)
			pos.x -= EVADESPEED * Time::DeltaTime();
		tr->SetPos(pos);
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

				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dash(Anticipate)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				tr->SetPos(pos);
			}

			gDashAnticipateFlag = true;
			idleFlag = false;
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
				mAnimator->Play(L"Hornet_G Dashleft", true);
			}
				
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-60.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_G Dashright", true);
			}

			gDashFlag = true;
			gDashAnticipateFlag = false;
			playerPos = Player::GetInstance()->GetComponent<Transform>()->GetPos();	// 패턴 시작시점 플레이어 pos
		}

		// 플레이어 방향으로 돌진
		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
			pos.x -= DASHSPEED * Time::DeltaTime();
		else if (mDirection == eDirection::Right)
			pos.x += DASHSPEED * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (playerPos.x - 10.0f <= pos.x && pos.x <= playerPos.x + 10.0f
			|| mTime >= 0.5f)	// dash 도중 playerPos.x 에 도달하면 dashrecover
		{
			mTime = 0.0f;
			mState = eHornetState::GDashRecover;
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

			gDashRecoverFlag = true;
			aDashFlag = false;
			gDashFlag = false;
		}
	}

	void Hornet::aDashAnticipate()
	{
		if (aDashAnticipateFlag == false)
		{
			// 플레이어 방향으로 방향 전환
			Vector2 playerPos = Player::GetInstance()->GetPos();
			if (playerPos.x > tr->GetPos().x)
				mDirection = eDirection::Right;
			else
				mDirection = eDirection::Left;

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

			jumpFlag = false;
			aDashAnticipateFlag = true;
			mRigidBody->SetActive(false);
		}

		mRigidBody->SetVelocity(Vector2::Zero);
	}

	void Hornet::aDash()
	{
		if (aDashFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(0.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dashleft", true);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-60.0f, -100.0f));
				mCollider->SetSize(Vector2(60.0f, 100.0f));
				mAnimator->Play(L"Hornet_A Dashright", true);
			}
			aDashFlag = true;
			aDashAnticipateFlag = false;

			playerPos = Player::GetInstance()->GetComponent<Transform>()->GetPos();	// 패턴 시작시점 플레이어 pos
			playerDir = playerPos - tr->GetPos();
			playerDir = playerDir.Normalize();
		}

		// 플레이어 방향으로 돌진
		Vector2 pos = tr->GetPos();
		pos.x += DASHSPEED * playerDir.x * Time::DeltaTime();
		pos.y += DASHSPEED * playerDir.y * Time::DeltaTime();
		tr->SetPos(pos);
		mRigidBody->SetVelocity(Vector2::Zero);

		if (playerPos.x - 10.0f <= pos.x && pos.x <= playerPos.x + 10.0f)	// dash 도중 playerPos.x 에 도달하면 dashrecover
		{
			if (mRigidBody->GetGround() == true)
			{
				mState = eHornetState::GDashRecover;
			}
			else
			{
				mState = eHornetState::ADashRecover;
			}
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

			aDashRecoverFlag = true;
			aDashFlag = false;
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

			sphereAnticipateGFlag = true;
			idleFlag = false;
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

			sphereAnticipateAFlag = true;
			jumpFlag = false;
			mRigidBody->SetActive(false);
		}

		mRigidBody->SetVelocity(Vector2::Zero);

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

			ball->SetState(eState::Active);
			ball->SetShereBallState(SphereBall::eSphereBallState::Active);

			sphereAnticipateAFlag = false;
			sphereAnticipateGFlag = false;
			sphereFlag = true;
		}

		mRigidBody->SetVelocity(Vector2::Zero);

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

			sphereRecoverFlag = true;
			sphereFlag = false;
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

				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-60.0f, -140.0f));
				mCollider->SetSize(Vector2(80.0f, 140.0f));
				mAnimator->Play(L"Hornet_Throw(Anticipate)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				tr->SetPos(pos);
			}

			throwNeedleAnticipateFlag = true;
			idleFlag = false;
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

				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				tr->SetPos(pos);

				needle->SetneedleDirection(eDirection::Left);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-65.0f, -100.0f));
				mCollider->SetSize(Vector2(130.0f, 100.0f));
				mAnimator->Play(L"Hornet_Throwright", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				tr->SetPos(pos);
				needle->SetneedleDirection(eDirection::Right);
			}
			needle->SetState(eState::Active);
			needle->SetNeedeState(HornetNeedle::eHornetNeedleState::Active);

			mTime += Time::DeltaTime();
			if (mTime >= 0.5f)
			{
				needleCatchFlag = true;
			}

			throwNeedleFlag = true;
			throwNeedleAnticipateFlag = false;
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

				Vector2 pos = tr->GetPos();
				pos.x += 50.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-65.0f, -100.0f));
				mCollider->SetSize(Vector2(130.0f, 100.0f));
				mAnimator->Play(L"Hornet_Throw(Recover)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 50.0f;
				tr->SetPos(pos);
			}

			throwNeedleRecoverFlag = true;
			throwNeedleFlag = false;
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

				Vector2 pos = tr->GetPos();
				pos.x += 40.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-92.5f, -120.0f));
				mCollider->SetSize(Vector2(185.0f, 120.0f));
				mAnimator->Play(L"Hornet_Counter(Anticipate)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 40.0f;
				tr->SetPos(pos);
			}

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
				mAnimator->Play(L"Hornet_Counter(Stance)left", true);

				Vector2 pos = tr->GetPos();
				pos.x += 40.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-92.5f, -120.0f));
				mCollider->SetSize(Vector2(185.0f, 120.0f));
				mAnimator->Play(L"Hornet_Counter(Stance)right", true);

				Vector2 pos = tr->GetPos();
				pos.x -= 40.0f;
				tr->SetPos(pos);
			}

			counterStanceFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 1.0f)
		{
			mTime = 0.0f;
			if (mDirection == eDirection::Left)
			{
				Vector2 pos = tr->GetPos();
				pos.x -= 40.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				Vector2 pos = tr->GetPos();
				pos.x += 40.0f;
				tr->SetPos(pos);
			}

			mState = eHornetState::CounterEnd;
			counterStanceFlag = false;
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

				Vector2 pos = tr->GetPos();
				pos.x += 40.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Counter(End)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 40.0f;
				tr->SetPos(pos);
			}

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

				Vector2 pos = tr->GetPos();
				pos.x -= 14.0f;
				//pos.y += 15.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-100.0f, -100.0f));
				mCollider->SetSize(Vector2(140.0f, 100.0f));
				mAnimator->Play(L"Hornet_Counter Attack(Anticipate)right", false);

				Vector2 pos = tr->GetPos();
				pos.x += 14.0f;
				//pos.y += 15.0f;
				tr->SetPos(pos);
			}

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
			caCol->SetState(eState::Active);
			caCol->SetCAState(CounterAttackCollider::eCounterAttackColliderState::Active);

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

				Vector2 pos = tr->GetPos();
				pos.x += 128.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(20.0f, -150.0f));
				mCollider->SetSize(Vector2(80.0f, 150.0f));
				mAnimator->Play(L"Hornet_Counter Attack(Recover)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 128.0f;
				tr->SetPos(pos);
			}

			counterAttackRecoverFlag = true;
		}
	}

	void Hornet::barbThrowAnticipate()
	{
		if (barbThrowAnticipateFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Barb Throw(Anticipate)left", false);

				Vector2 pos = tr->GetPos();
				pos.x += 13.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mCollider->SetCenter(Vector2(-30.0f, -170.0f));
				mCollider->SetSize(Vector2(60.0f, 170.0f));
				mAnimator->Play(L"Hornet_Barb Throw(Anticipate)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 13.0f;
				tr->SetPos(pos);
			}

			barbThrowAnticipateFlag = true;
		}
	}

	void Hornet::barbThrow()
	{
		if (barbThrowFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mAnimator->Play(L"Hornet_Barb Throwleft", false);

				Vector2 pos = tr->GetPos();
				pos.x += 13.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mAnimator->Play(L"Hornet_Barb Throwright", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 13.0f;
				tr->SetPos(pos);
			}

			barbThrowFlag = true;
		}
	}

	void Hornet::barbThrowRecover()
	{
		if (barbThrowRecoverFlag == false)
		{
			if (mDirection == eDirection::Left)
			{
				mAnimator->Play(L"Hornet_Barb Throw(Recover)left", false);

				Vector2 pos = tr->GetPos();
				pos.x += 13.0f;
				tr->SetPos(pos);
			}
			else if (mDirection == eDirection::Right)
			{
				mAnimator->Play(L"Hornet_Barb Throw(Recover)right", false);

				Vector2 pos = tr->GetPos();
				pos.x -= 13.0f;
				tr->SetPos(pos);
			}

			barbThrowRecoverFlag = true;
		}
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

	void Hornet::jumpAnticipateCompleteEvent()
	{
		mState = eHornetState::Jump;
	}

	void Hornet::jumpCompleteEvent()
	{
		// Jump에서 선택한 변수값으로 이후 패턴 실행
		// 1) 아무것도 하지 않고 착지
		// 2) sphere
		// 3) dash

		if (jumpPattern == 0)	// 아무것도 하지 않고 착지
		{

		}
		else if (jumpPattern == 1)	// sphere
		{
			mState = eHornetState::SphereAnticipateA;
		}
		else if (jumpPattern == 2)	// dash
		{
			mState = eHornetState::ADashAnticipate;
		}

		//jumpPattern = -1;
	}

	void Hornet::landCompleteEvent()
	{
		mState = eHornetState::Idle;
	}

	void Hornet::sphereAnticipateACompleteEvent()
	{
		mState = eHornetState::Sphere;
	}

	void Hornet::sphereAnticipateGCompleteEvent()
	{
		mState = eHornetState::Sphere;
	}

	void Hornet::sphereCompleteEvent()
	{
		mState = eHornetState::SphereRecover;
	}

	void Hornet::sphereRecoverCompleteEvent()
	{
		if (mRigidBody->GetGround() == true)
		{
			mState = eHornetState::Idle;
		}

		mRigidBody->SetActive(true);
	}

	void Hornet::aDashAnticipateCompleteEvent()
	{
		mState = eHornetState::ADash;
	}

	void Hornet::aDashRecoverCompleteEvent()
	{
		//mState = eHornetState::Idle;
		mRigidBody->SetActive(true);
	}

	void Hornet::aDashCompleteEvent()
	{
		
	}

	void Hornet::gDashAnticipateCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::GDash;
	}

	void Hornet::gDashRecoverCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::Idle;
	}

	void Hornet::gDashCompleteEvent()
	{

	}

	void Hornet::throwNeedleAnticipateCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::ThrowNeedle;
		throwNeedleAnticipateFlag = false;
	}

	void Hornet::throwNeedleCompleteEvent()
	{
		/*
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::ThrowNeedleRecover;
		throwNeedleFlag = false;
		*/
	}

	void Hornet::throwNeedleRecoverCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 50.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::Idle;
		throwNeedleRecoverFlag = false;
	}

	void Hornet::counterAnticipateCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 40.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 40.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::CounterStance;
		counterAnticipateFlag = false;
	}

	void Hornet::counterStanceCompleteEvent()
	{

	}

	void Hornet::counterEndCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			//pos.x -= 40.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			//pos.x += 40.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::Idle;
		counterEndFlag = false;
	}

	void Hornet::counterAttackAnticipateCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 14.0f;
			//pos.y -= 15.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 14.0f;
			//pos.y -= 15.0f;
			tr->SetPos(pos);
		}

		mState = eHornetState::CounterAttack;
		counterAttackAnticipateFlag = false;
	}

	void Hornet::counterAttackCompleteEvent()
	{
		mState = eHornetState::CounterAttackRecover;
		counterAttackFlag = false;
	}

	void Hornet::counterAttackRecoverCompleteEvent()
	{
		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 128.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 128.0f;
			tr->SetPos(pos);
		}
		mState = eHornetState::Idle;
		counterAttackRecoverFlag = false;
	}

	void Hornet::evadeAnticipateCompleteEvent()
	{
		mState = eHornetState::Evade;
		evadeAnticipateFlag = false;
	}

	void Hornet::evadeCompleteEvent()
	{
		mState = eHornetState::Idle;
		evadeFlag = false;
	}

	void Hornet::runCompleteEvent()
	{
		mState = eHornetState::Idle;
		runFlag = false;
	}

	void Hornet::barbThrowAnticipateCompleteEvent()
	{
		mState = eHornetState::BarbThrow;
		barbThrowAnticipateFlag = false;

		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 13.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 13.0f;
			tr->SetPos(pos);
		}
	}

	void Hornet::barbThrowCompleteEvent()
	{
		mState = eHornetState::BarbThrowRecover;
		barbThrowFlag = false;

		//barb01->SetState(eState::Active);
		//barb02->SetState(eState::Active);
		//barb03->SetState(eState::Active);
		//barb04->SetState(eState::Active);
		barb01->SetBarbState(Barb01::eBarbState::Active);
		barb02->SetBarbState(Barb02::eBarbState::Active);
		barb03->SetBarbState(Barb03::eBarbState::Active);
		barb04->SetBarbState(Barb04::eBarbState::Active);

		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 13.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 13.0f;
			tr->SetPos(pos);
		}
	}

	void Hornet::barbThrowRecoverCompleteEvent()
	{
		mState = eHornetState::Idle;
		barbThrowRecoverFlag = false;

		if (mDirection == eDirection::Left)
		{
			Vector2 pos = tr->GetPos();
			pos.x -= 13.0f;
			tr->SetPos(pos);
		}
		else if (mDirection == eDirection::Right)
		{
			Vector2 pos = tr->GetPos();
			pos.x += 13.0f;
			tr->SetPos(pos);
		}
	}

	void Hornet::initializeFlag()
	{
		//idleFlag = false;
		runFlag = false;
		jumpAnticipateFlag = false;
		jumpFlag = false;
		landFlag = false;
		evadeAnticipateFlag = false;
		evadeFlag = false;
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
		eventFlag = false;
	}
}
