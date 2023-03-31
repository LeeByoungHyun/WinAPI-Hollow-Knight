#include "FalseKnight.h"
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

#include "yaPlayer.h"

namespace ya
{
	FalseKnight* FalseKnight::instance = nullptr;

	FalseKnight::FalseKnight()
	{

	}

	FalseKnight::~FalseKnight()
	{

	}

	void FalseKnight::Initialize()
	{
		mRigidbody = AddComponent<RigidBody>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Idle\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Land\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Land\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Up)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Up)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 1)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 1)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 2)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 2)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 3)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 3)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll End)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll End)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Open)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Open)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Opened)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Opened)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Hit)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Hit)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Idle)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Idle)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 1)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 1)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 2)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 2)\\right", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"False Knight_Jump(Anticipate)left") = std::bind(&FalseKnight::jumpAnticipateComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Jump(Anticipate)right") = std::bind(&FalseKnight::jumpAnticipateComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Landleft") = std::bind(&FalseKnight::landComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Landright") = std::bind(&FalseKnight::landComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Jump Attack(Part 1)left") = std::bind(&FalseKnight::jumpAttackPart1ComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Jump Attack(Part 1)right") = std::bind(&FalseKnight::jumpAttackPart1ComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Jump Attack(Part 2)left") = std::bind(&FalseKnight::jumpAttackPart2ComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Jump Attack(Part 2)right") = std::bind(&FalseKnight::jumpAttackPart2ComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Jump Attack(Part 3)left") = std::bind(&FalseKnight::jumpAttackPart3ComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Jump Attack(Part 3)right") = std::bind(&FalseKnight::jumpAttackPart3ComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Attack(Anticipate)left") = std::bind(&FalseKnight::attackAnticipateComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Attack(Anticipate)right") = std::bind(&FalseKnight::attackAnticipateComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Attackleft") = std::bind(&FalseKnight::attackComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Attackright") = std::bind(&FalseKnight::attackComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Attack(Recover)left") = std::bind(&FalseKnight::attackRecoverComplateEvent, this);
		mAnimator->GetCompleteEvent(L"False Knight_Attack(Recover)right") = std::bind(&FalseKnight::attackRecoverComplateEvent, this);
		
		mState = eFalseKnightState::Idle;
		mDirection = eDirection::Left;

		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 2000.0f));

		GameObject::Initialize();
	}

	void FalseKnight::Update()
	{
		GameObject::Update();

		// 플레이어 위치에 따라 방향 전환
		if (mState == eFalseKnightState::Idle)
		{
			Vector2 playerPos = Player::GetInstance()->GetPos();
			if (playerPos.x > tr->GetPos().x)
				mDirection = eDirection::Right;
			else
				mDirection = eDirection::Left;
		}

		/*
		// 테스트
		Vector2 playerPos = Player::GetInstance()->GetPos();
		if (playerPos.x > tr->GetPos().x)
			mDirection = eDirection::Right;
		else
			mDirection = eDirection::Left;
		mTime += Time::DeltaTime();
		if (mTime >= 2.0f)
		{
			mState = eFalseKnightState::JumpAnticipate;

			idleFlag = false;
			runAnticipateFlag = false;
			runFlag = false;
			jumpAnticipateFlag = false;
			jumpFlag = false;
			landFlag = false;
			attackAnticipateFlag = false;
			attackFlag = false;
			attackRecoverFlag = false;
			jumpAttackUpFlag = false;
			jumpAttackPart1Flag = false;
			jumpAttackPart2Flag = false;
			jumpAttackPart3Flag = false;
			stunRollFlag = false;
			stunRollEndFlag = false;
			stunOpenFlag = false;
			stunOpenedFlag = false;
			stunHitFlag = false;
			deathFlag = false;
			jumpReadyFlag = false;

			mTime = 0.0f;
		}
		*/

		switch (mState)
		{
		case ya::FalseKnight::eFalseKnightState::Idle:
			idle();
			break;

		case ya::FalseKnight::eFalseKnightState::RunAnticipate:
			runAnticipate();
			break;

		case ya::FalseKnight::eFalseKnightState::Run:
			run();
			break;

		case ya::FalseKnight::eFalseKnightState::JumpAnticipate:
			jumpAnticipate();
			break;

		case ya::FalseKnight::eFalseKnightState::Jump:
			jump();
			break;

		case ya::FalseKnight::eFalseKnightState::Land:
			land();
			break;

		case ya::FalseKnight::eFalseKnightState::AttackAnticipate:
			attackAnticipate();
			break;

		case ya::FalseKnight::eFalseKnightState::Attack:
			attack();
			break;

		case ya::FalseKnight::eFalseKnightState::AttackRecover:
			attackRecover();
			break;

		case ya::FalseKnight::eFalseKnightState::JumpAttackUp:
			jumpAttackUp();
			break;

		case ya::FalseKnight::eFalseKnightState::JumpAttackPart1:
			jumpAttackPart1();
			break;

		case ya::FalseKnight::eFalseKnightState::JumpAttackPart2:
			jumpAttackPart2();
			break;

		case ya::FalseKnight::eFalseKnightState::JumpAttackPart3:
			jumpAttackPart3();
			break;

		case ya::FalseKnight::eFalseKnightState::StunRoll:
			stunRoll();
			break;

		case ya::FalseKnight::eFalseKnightState::StunRollEnd:
			stunRollEnd();
			break;

		case ya::FalseKnight::eFalseKnightState::StunOpen:
			stunOpen();
			break;

		case ya::FalseKnight::eFalseKnightState::StunOpened:
			stunOpened();
			break;

		case ya::FalseKnight::eFalseKnightState::StunHit:
			stunHit();
			break;

		case ya::FalseKnight::eFalseKnightState::Death:
			death();
			break;

		default:
			break;
		}
	}

	void FalseKnight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseKnight::Release()
	{
		GameObject::Release();
	}

	void FalseKnight::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		eLayerType otherType = other->GetOwner()->GetType();	// 플레이어와 충돌한 객체의 타입
		switch (otherType)
		{
		// 땅과 충돌할 경우
		case eLayerType::Ground:
			mRigidbody->SetGround(true);
			mRigidbody->SetVelocity(Vector2::Zero);
			// 점프애니메이션 도중 땅에 착지하면 Land animation 재생
			if (mState == FalseKnight::eFalseKnightState::Jump)
			{
				mState = FalseKnight::eFalseKnightState::Land;
			}
			else if (mState == FalseKnight::eFalseKnightState::JumpAttackUp)
			{
				mState = FalseKnight::eFalseKnightState::JumpAttackPart1;
			}
			break;
		}
	}

	void FalseKnight::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void FalseKnight::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void FalseKnight::idle()
	{
		if (idleFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-135.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Idleleft", true);
				idleFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-140.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Idleright", true);
				idleFlag = true;
				break;

			default:
				break;
			}

			runFlag = false;
			landFlag = false;
			attackRecoverFlag = false;
			jumpAttackPart3Flag = false;
		}
	}

	void FalseKnight::runAnticipate()
	{
		if (runAnticipateFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-250.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Run(Anticipate)left", false);
				runAnticipateFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-25.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Run(Anticipate)right", false);
				runAnticipateFlag = true;
				break;

			default:
				break;
			}

			idleFlag = false;
		}
	}

	void FalseKnight::run()
	{
		if (runFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-250.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Runleft", false);
				runFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-25.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Runright", false);
				runFlag = true;
				break;

			default:
				break;
			}

			runAnticipateFlag = false;
		}
	}

	void FalseKnight::jumpAnticipate()
	{
		if (jumpAnticipateFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-140.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump(Anticipate)left", false);
				jumpAnticipateFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-135.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump(Anticipate)right", false);
				jumpAnticipateFlag = true;
				break;

			default:
				break;
			}

			idleFlag = false;
		}
	}

	void FalseKnight::jump()
	{
		if (jumpFlag == false)
		{
			//Vector2 pos = tr->GetPos();
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-140.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));
				//pos.x += 60.0f;
				//tr->SetPos(pos);

				mAnimator->Play(L"False Knight_Jumpleft", false);
				jumpFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-135.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));
				//pos.x -= 60.0f;
				//tr->SetPos(pos);

				mAnimator->Play(L"False Knight_Jumpright", false);
				jumpFlag = true;
				break;

			default:
				break;
			}

			jumpAnticipateFlag = false;
			jumpReadyFlag = false;
		}
	}

	void FalseKnight::land()
	{
		if (landFlag == false)
		{
			//Vector2 pos = tr->GetPos();
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-145.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));
				//pos.x -= 60.0f;
				//tr->SetPos(pos);

				mAnimator->Play(L"False Knight_Landleft", false);
				landFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-130.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));
				//pos.x += 60.0f;
				//tr->SetPos(pos);

				mAnimator->Play(L"False Knight_Landright", false);
				landFlag = true;
				break;

			default:
				break;
			}

			jumpFlag = false;
		}
	}

	void FalseKnight::attackAnticipate()
	{
		if (attackAnticipateFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-100.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attack(Anticipate)left", false);
				attackAnticipateFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-175.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attack(Anticipate)right", false);
				attackAnticipateFlag = true;
				break;

			default:
				break;
			}

			idleFlag = false;
		}
	}

	void FalseKnight::attack()
	{
		if (attackFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-125.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attackleft", false);
				attackFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-150.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attackright", false);
				attackFlag = true;
				break;

			default:
				break;
			}

			attackAnticipateFlag = false;
		}
	}

	void FalseKnight::attackRecover()
	{
		if (attackRecoverFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-150.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attack(Recover)left", false);
				attackRecoverFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-125.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attack(Recover)right", false);
				attackRecoverFlag = true;
				break;

			default:
				break;
			}

			attackFlag = false;
		}
	}

	void FalseKnight::jumpAttackUp()
	{
		if (jumpAttackUpFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-97.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Up)left", false);
				jumpAttackUpFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-178.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Up)right", false);
				jumpAttackUpFlag = true;
				break;

			default:
				break;
			}

			jumpAnticipateFlag = false;
			jumpReadyFlag = false;
		}
	}

	void FalseKnight::jumpAttackPart1()
	{
		if (jumpAttackPart1Flag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-190.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 1)left", false);
				jumpAttackPart1Flag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-85.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 1)right", false);
				jumpAttackPart1Flag = true;
				break;

			default:
				break;
			}

			jumpAttackUpFlag = false;
		}
	}

	void FalseKnight::jumpAttackPart2()
	{
		if (jumpAttackPart2Flag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-190.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 2)left", false);
				jumpAttackPart2Flag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-85.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 2)right", false);
				jumpAttackPart2Flag = true;
				break;

			default:
				break;
			}

			jumpAttackPart1Flag = false;
		}
	}

	void FalseKnight::jumpAttackPart3()
	{
		if (jumpAttackPart3Flag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-132.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 3)left", false);
				jumpAttackPart3Flag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-143.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 3)right", false);
				jumpAttackPart3Flag = true;
				break;

			default:
				break;
			}

			jumpAttackPart2Flag = false;
		}
	}

	void FalseKnight::stunRoll()
	{
		if (stunRollFlag == false)
		{
			mCollider->SetActive(false);
			mCollider->SetCenter(Vector2(0.0f, 0.0f));
			mCollider->SetSize(Vector2(0.0f, 0.0f));

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"False Knight_Stun(Roll)left", false);
				stunRollFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"False Knight_Stun(Roll)right", false);
				stunRollFlag = true;
				break;

			default:
				break;
			}


		}
	}

	void FalseKnight::stunRollEnd()
	{
		if (stunRollEndFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"False Knight_Stun(Roll End)left", false);
				stunRollEndFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"False Knight_Stun(Roll End)right", false);
				stunRollEndFlag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::stunOpen()
	{
		if (stunOpenFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"False Knight_Stun(Open)left", false);
				stunOpenFlag = true;
				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"False Knight_Stun(Open)right", false);
				stunOpenFlag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::stunOpened()
	{

	}

	void FalseKnight::stunHit()
	{

	}

	void FalseKnight::death()
	{

	}

	void FalseKnight::jumpAnticipateComplateEvent()
	{
		//mState = eFalseKnightState::Jump;
		jumpReadyFlag = true;
	}

	void FalseKnight::jumpComplateEvent()
	{

	}

	void FalseKnight::landComplateEvent()
	{
		mState = eFalseKnightState::Idle;
	}

	void FalseKnight::jumpAttackPart1ComplateEvent()
	{
		mState = eFalseKnightState::JumpAttackPart2;
	}

	void FalseKnight::jumpAttackPart2ComplateEvent()
	{
		mState = eFalseKnightState::JumpAttackPart3;
	}

	void FalseKnight::jumpAttackPart3ComplateEvent()
	{
		mState = eFalseKnightState::Idle;
	}

	void FalseKnight::attackAnticipateComplateEvent()
	{
		mState = eFalseKnightState::Attack;
	}

	void FalseKnight::attackComplateEvent()
	{
		mState = eFalseKnightState::AttackRecover;
	}

	void FalseKnight::attackRecoverComplateEvent()
	{
		mState = eFalseKnightState::Idle;
	}
}