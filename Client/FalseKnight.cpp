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
		//mRigidbody = AddComponent<RigidBody>();
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

		mAnimator->Play(L"False Knight_Idleleft", true);
		mState = eFalseKnightState::Idle;
		mDirection = eDirection::Left;

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
	}

	void FalseKnight::runAnticipate()
	{

	}

	void FalseKnight::run()
	{

	}

	void FalseKnight::jumpAnticipate()
	{

	}

	void FalseKnight::jump()
	{

	}

	void FalseKnight::land()
	{

	}

	void FalseKnight::attackAnticipate()
	{

	}

	void FalseKnight::attack()
	{

	}

	void FalseKnight::attackRecover()
	{

	}

	void FalseKnight::jumpAttackUp()
	{

	}

	void FalseKnight::jumpAttackPart1()
	{

	}

	void FalseKnight::jumpAttackPart2()
	{

	}

	void FalseKnight::jumpAttackPart3()
	{

	}

	void FalseKnight::stunRoll()
	{

	}

	void FalseKnight::stunRollEnd()
	{

	}

	void FalseKnight::stunOpen()
	{

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