#include "FalseKnightManager.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaRigidBody.h"

#include "FalseKnight.h"
#include "yaPlayer.h"

namespace ya
{
	FalseKnightManager::FalseKnightManager()
	{

	}

	FalseKnightManager::~FalseKnightManager()
	{

	}

	void FalseKnightManager::Initialize()
	{
		mFalseKnight = FalseKnight::GetInstance();

		GameObject::Initialize();
	}

	void FalseKnightManager::Update()
	{
		activeScene = SceneManager::GetActiveScene();
		if (activeScene->GetType() == eSceneType::FalseKnightBoss && count1 == false)
		{
			mPhase = ePhaseState::Phase1;
			count1 = true;
		}

		switch (mPhase)
		{
		case ya::FalseKnightManager::ePhaseState::Phase1:
			phase1();
			break;

		case ya::FalseKnightManager::ePhaseState::Pattern1:
			pattern1();
			break;

		case ya::FalseKnightManager::ePhaseState::Pattern2:
			pattern2();
			break;

		case ya::FalseKnightManager::ePhaseState::Pattern3:
			pattern3();
			break;

		case ya::FalseKnightManager::ePhaseState::Pattern4:
			pattern4();
			break;

		default:
			break;
		}
		GameObject::Update();
	}

	void FalseKnightManager::Release()
	{
		GameObject::Release();
	}

	void FalseKnightManager::phase1()
	{
		// Idle 상태에서 일정 시간이 지나면 패턴중 하나를 랜덤하게 실행
		mTime += Time::DeltaTime();
		if (mTime >= 1.5f && mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle)
		{
			srand((unsigned int)time(NULL));
			//pattern = rand() % 4;	
			pattern = 0;
			mTime = 0.0f;
			switch (pattern)
			{
			case 0:	// Jump to Player
				mPhase = ePhaseState::Pattern1;
				break;

			case 1:	// Jump Attack to Player
				mPhase = ePhaseState::Pattern2;
				break;

			case 2:	// Attack
				mPhase = ePhaseState::Pattern3;
				break;

			case 3:	// Attack after jump away from player
				mPhase = ePhaseState::Pattern4;
				break;

			default:
				mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Idle);
				break;
			}
		}
	}

	void FalseKnightManager::phase2()
	{

	}

	void FalseKnightManager::pattern1()
	{
		if (pattern1Flag == false)
		{
			pattern1Flag = true;

			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::JumpAnticipate);
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Jump && flag2 == false)
		{
			flag2 = true;

			// 플레이어와의 거리에 비례해서 더 멀리 점프해야 함
			Vector2 distance = Vector2::Zero;
			distance.x = Player::GetInstance()->GetComponent<Transform>()->GetPos().x
				- mFalseKnight->GetComponent<Transform>()->GetPos().x;

			mFalseKnight->GetComponent<RigidBody>()->SetVelocity(Vector2(distance.x / 2, -1500.0f));
			mFalseKnight->GetComponent<RigidBody>()->SetGround(false);
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle && pattern1Flag == true)
		{
			mPhase = ePhaseState::Phase1; 
			pattern1Flag = false;
			flag2 = false;
		}
	}

	void FalseKnightManager::pattern2()
	{

	}

	void FalseKnightManager::pattern3()
	{

	}

	void FalseKnightManager::pattern4()
	{

	}
}