#include "FalseKnightManager.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaRigidBody.h"

#include "FalseKnight.h"
#include "StunHead.h"
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
		// �÷��̾ ������ �����ϸ� ����
		activeScene = SceneManager::GetActiveScene();
		if (activeScene->GetType() == eSceneType::FalseKnightBoss && enterFlag == false)
		{
			mPhase = ePhaseState::Phase1;
			enterFlag = true;
		}

		if (stuned == false)
		{
			// ���� ü���� 0�� �Ǹ� ����
			if (mFalseKnight->GetArmorHP() <= 0 && stunFlag == false)
			{
				mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::StunRoll);
				mFalseKnight->IncreaseStunCount();
				mFalseKnight->InitializeFlag();
				stunFlag = true;
				stuned = true;
			}
		}
		else if (stuned == true)
		{
			// ��ü ü���� 0�� �Ǹ� Death
			if (mFalseKnight->GetTrueHP() <= 0)
			{
				mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Death);
			}
			// ��ü ü���� 40*���Ϲ���� �Ǹ� Idle
			else if (mFalseKnight->GetTrueHP() <= 160 - (mFalseKnight->GetStunCount() * 40))
			{
				mFalseKnight->SetTrueHP(160 - (mFalseKnight->GetStunCount() * 40));
				mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Idle);	// �Ͼ�� �ִϸ��̼����� ���� ����
				mFalseKnight->InitializeFlag();
				mFalseKnight->SetArmorHP(75);
				stunFlag = false;
				stuned = false;
				mPhase = ePhaseState::Rage;
			}
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

		case ya::FalseKnightManager::ePhaseState::Rage:
			rage();
			break;

		case ya::FalseKnightManager::ePhaseState::RageAttack:
			rageAttack();
			break;

		case ya::FalseKnightManager::ePhaseState::Stun:
			stun();
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
		// Idle ���¿��� ���� �ð��� ������ ������ �ϳ��� �����ϰ� ����
		mTime += Time::DeltaTime();
		if (mTime >= 1.5f && mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle)
		{
			srand((unsigned int)time(NULL));
			pattern = rand() % 4;	
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
		/* �÷��̾� ��ġ�� ���� */ 
		if (pattern1Flag == false)
		{
			pattern1Flag = true;

			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::JumpAnticipate);
		}

		if (mFalseKnight->GetJumpReadyFlag() == true && check1Flag == false)
		{
			check1Flag = true;
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Jump);

			// �÷��̾���� �Ÿ��� ����ؼ� �� �ָ� �����ؾ� ��
			Vector2 distance = Vector2::Zero;
			distance.x = Player::GetInstance()->GetComponent<Transform>()->GetPos().x
				- mFalseKnight->GetComponent<Transform>()->GetPos().x;
			mFalseKnight->GetComponent<RigidBody>()->SetVelocity(Vector2(distance.x / 1.5f, -1500.0f));
			mFalseKnight->GetComponent<RigidBody>()->SetGround(false);
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle && pattern1Flag == true)
		{
			mPhase = ePhaseState::Phase1;
			pattern1Flag = false;
			check1Flag = false;
		}
	}

	void FalseKnightManager::pattern2()
	{
		/* �÷��̾� ��ġ�� �����ϸ鼭 ���� */
		if (pattern1Flag == false)
		{
			pattern1Flag = true;

			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::JumpAnticipate);
		}

		if (mFalseKnight->GetJumpReadyFlag() == true && check1Flag == false)
		{
			check1Flag = true;
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::JumpAttackUp);

			// �÷��̾���� �Ÿ��� ����ؼ� �� �ָ� �����ؾ� ��
			Vector2 distance = Vector2::Zero;
			distance.x = Player::GetInstance()->GetComponent<Transform>()->GetPos().x
				- mFalseKnight->GetComponent<Transform>()->GetPos().x;
			mFalseKnight->GetComponent<RigidBody>()->SetVelocity(Vector2(distance.x / 1.5f, -1500.0f));
			mFalseKnight->GetComponent<RigidBody>()->SetGround(false);
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle && pattern1Flag == true)
		{
			mPhase = ePhaseState::Phase1;
			pattern1Flag = false;
			check1Flag = false;
		}
	}

	void FalseKnightManager::pattern3()
	{
		/* ���ڸ����� ���� */
		if (pattern1Flag == false)
		{
			pattern1Flag = true;

			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::AttackAnticipate);
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle && pattern1Flag == true)
		{
			mPhase = ePhaseState::Phase1;
			pattern1Flag = false;
		}
	}

	void FalseKnightManager::pattern4()
	{
		/* �÷��̾��� �ݴ�������� ���� �� ���� */
		if (pattern1Flag == false)
		{
			pattern1Flag = true;

			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::JumpAnticipate);
		}

		if (mFalseKnight->GetJumpReadyFlag() == true && check1Flag == false)
		{
			check1Flag = true;
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Jump);

			// �÷��̾��� �ݴ������� ���� �Ÿ���ŭ �����ؾ� ��
			if ((Player::GetInstance()->GetComponent<Transform>()->GetPos().x
				- mFalseKnight->GetComponent<Transform>()->GetPos().x) < 0)
				mFalseKnight->GetComponent<RigidBody>()->SetVelocity(Vector2(400.0f, -1500.0f));
			else
				mFalseKnight->GetComponent<RigidBody>()->SetVelocity(Vector2(-400.0f, -1500.0f));

			mFalseKnight->GetComponent<RigidBody>()->SetGround(false);
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle 
			&& check1Flag == true && check2Flag == false)
		{
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::AttackAnticipate);
			check2Flag = true;
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle && pattern1Flag == true)
		{
			mPhase = ePhaseState::Phase1;
			pattern1Flag = false;
			check1Flag = false;
			check2Flag = false;
		}
	}

	void FalseKnightManager::rage()
	{
		/* �� �߾����� ���� �� �¿� ������� �ݺ� */
		if (rageFlag == false)
		{
			rageFlag = true;

			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::JumpAnticipate);
		}

		if (mFalseKnight->GetJumpReadyFlag() == true)
		{
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Jump);

			Vector2 distance = Vector2::Zero;
			distance.x = 1724.0f // �� �߾� x��ǥ
				- mFalseKnight->GetComponent<Transform>()->GetPos().x;
			mFalseKnight->GetComponent<RigidBody>()->SetVelocity(Vector2(distance.x / 1.5f, -1500.0f));
			mFalseKnight->GetComponent<RigidBody>()->SetGround(false);
		}

		// �߾����� ���� �� 5���� �¿쳻�����
		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle && rageFlag == true)
		{
			mPhase = ePhaseState::RageAttack;
			rageFlag = false;
			check1Flag = false;
		}
	}

	void FalseKnightManager::stun()
	{
		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle)
		{
			mPhase = ePhaseState::Phase1;
		}
	}

	void FalseKnightManager::rageAttack()
	{
		if (rageAttackFlag == false)
		{
			rageAttackFlag = true;
			mFalseKnight->SetRageFlag(true);
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::AttackAnticipate);
		}

		if (mFalseKnight->GetRageFlag() == false && mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::Idle)
		{
			rageAttackFlag = false;
			mPhase = ePhaseState::Phase1;
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Idle);
			mFalseKnight->InitializeFlag();
		}

		/*
		// �¿� ������� 5�� �ݺ�
		if (rageAttackFlag == false)
		{
			rageAttackFlag = true;

			// �� ���ݸ��� ���� ��ȯ
			if (mFalseKnight->GetDirection() == FalseKnight::eDirection::Left)
				mFalseKnight->SetDirection(FalseKnight::eDirection::Right);
			else
				mFalseKnight->SetDirection(FalseKnight::eDirection::Left);

			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Attack);
			rageCount++;
		}

		if (mFalseKnight->GetFalseKnightState() == FalseKnight::eFalseKnightState::AttackRecover && rageAttackFlag == true)
		{
			rageAttackFlag = false;
			mFalseKnight->InitializeFlag();

			// ������ġ����
			Vector2 pos = mFalseKnight->GetComponent<Transform>()->GetPos();
			pos.y += 20.0f;
			mFalseKnight->GetComponent<Transform>()->SetPos(pos);
		}

		if (rageCount > 10)
		{
			mPhase = ePhaseState::Phase1;
			mFalseKnight->SetFalseKnightState(FalseKnight::eFalseKnightState::Idle);
			mFalseKnight->InitializeFlag();
			rageAttackFlag = false;
			rageCount = 0;
		}
		*/
	}
}