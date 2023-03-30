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
		Vector2 playerPos = Player::GetInstance()->GetPos();
		if (playerPos.x > tr->GetPos().x)
			mDirection = eDirection::Right;
		else
			mDirection = eDirection::Left;

		// 테스트용 코드
		mTime += Time::DeltaTime();
		if (mTime >= 1.0f)
		{
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
			mTime = 0.0f;
		}

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
				mCollider->SetCenter(Vector2(-200.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Idleleft", true);
				idleFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-75.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Idleright", true);
				idleFlag = true;
				break;

			default:
				break;
			}
		}

		// Idle 상태에서 일정 시간이 지나면 패턴중 하나를 랜덤하게 실행
		mTime += Time::DeltaTime();
		if (mTime >= 1.5f)
		{
			srand((unsigned int)time(NULL));
			//pattern = rand() % 4;	
			pattern = 0;
			mTime = 0.0f;
			idleFlag = false;
			switch (pattern)
			{
			case 0:	// Jump to Player
				mState = eFalseKnightState::JumpAnticipate;
				break;

			case 1:	// Jump Attack to Player
				mState = eFalseKnightState::JumpAnticipate;
				break;

			case 2:	// Attack
				break;

			case 3:	// Attack after jump away from player
				mState = eFalseKnightState::JumpAnticipate;
				break;

			default:
				mState = eFalseKnightState::Idle;
				break;
			}
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
		}
	}

	void FalseKnight::jumpAnticipate()
	{
		if (jumpAnticipateFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-200.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump(Anticipate)left", false);
				jumpAnticipateFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-75.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump(Anticipate)right", false);
				jumpAnticipateFlag = true;
				break;

			default:
				break;
			}
		}

		// pattern 변수에 따라 다른 방향으로 점프해야 함
		switch(pattern)
		{
		case 0:	// Jump to Player
			break;

		case 1:	// Jump Attack to Player
			break;

		case 2:	// Attack
			break;

		case 3:	// Attack after jump away from player
			break;

		default:
			break;
		}


	}

	void FalseKnight::jump()
	{
		if (jumpFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-260.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jumpleft", false);
				jumpFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-15.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jumpright", false);
				jumpFlag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::land()
	{
		if (landFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-200.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Landleft", false);
				landFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-75.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Landright", false);
				landFlag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::attackAnticipate()
	{
		if (attackAnticipateFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-260.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attack(Anticipate)left", false);
				attackAnticipateFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-15.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attack(Anticipate)right", false);
				attackAnticipateFlag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::attack()
	{
		if (attackFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-60.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attackleft", false);
				attackFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-215.0f, -320.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Attackright", false);
				attackFlag = true;
				break;

			default:
				break;
			}
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
		}
	}

	void FalseKnight::jumpAttackUp()
	{
		if (jumpAttackUpFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-260.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Up)left", false);
				jumpAttackUpFlag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-15.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Up)right", false);
				jumpAttackUpFlag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::jumpAttackPart1()
	{
		if (jumpAttackPart1Flag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-210.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 1)left", false);
				jumpAttackPart1Flag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-65.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 1)right", false);
				jumpAttackPart1Flag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::jumpAttackPart2()
	{
		if (jumpAttackPart2Flag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-210.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 2)left", false);
				jumpAttackPart2Flag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-65.0f, -350.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 2)right", false);
				jumpAttackPart2Flag = true;
				break;

			default:
				break;
			}
		}
	}

	void FalseKnight::jumpAttackPart3()
	{
		if (jumpAttackPart3Flag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-170.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 3)left", false);
				jumpAttackPart3Flag = true;
				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-105.0f, -300.0f));
				mCollider->SetSize(Vector2(275.0f, 300.0f));

				mAnimator->Play(L"False Knight_Jump Attack(Part 3)right", false);
				jumpAttackPart3Flag = true;
				break;

			default:
				break;
			}
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
}