#include "MantisLordsManager.h"
#include "MantisLord1.h"
#include "MantisLord2.h"
#include "MantisLord3.h"
#include "yaSceneManager.h"
#include "yaTime.h"

namespace ya
{
	MantisLordsManager::MantisLordsManager()
	{

	}

	MantisLordsManager::~MantisLordsManager()
	{

	}

	void MantisLordsManager::Initialize()
	{
		GameObject::Initialize();

		mantisLord1 = MantisLord1::GetInstance();
		mantisLord2 = MantisLord2::GetInstance();
		mantisLord3 = MantisLord3::GetInstance();
	}

	void MantisLordsManager::Update()
	{
		GameObject::Update();

		activeScene = SceneManager::GetActiveScene();

		// �÷��̾ ������ ���Խ� 1������ ����
		if (activeScene->GetType() == eSceneType::MantisLordsBoss && StartFlag1 == false)
		{
			mPhase = ePhaseState::Phase1Start;
		}

		// 2, 3�� ������ �Ѹ����� ������ 3������ ����
		if ((mantisLord2->GetState() == MantisLord2::eMantisLordsState::ThroneWounded 
			|| mantisLord3->GetState() == MantisLord3::eMantisLordsState::ThroneWounded)
			&& StartFlag2 == false)
		{
			mPhase = ePhaseState::Phase3;
		}

		// ��� ������ ������ ���� �λ� �ִϸ��̼� ��� �� �� ����
		if (mantisLord1->GetState() == MantisLord1::eMantisLordsState::ThroneWounded 
			&& mantisLord2->GetState() == MantisLord2::eMantisLordsState::ThroneWounded
			&& mantisLord3->GetState() == MantisLord3::eMantisLordsState::ThroneWounded
			&& flag4 == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 5.0f)
			{
				mantisLord1->SetState(MantisLord1::eMantisLordsState::ThroneBow);
				mantisLord2->SetState(MantisLord2::eMantisLordsState::ThroneBow);
				mantisLord3->SetState(MantisLord3::eMantisLordsState::ThroneBow);

				mTime = 0.0f;
				flag4 = true;
			}
		}

		// ��� ������ ������ ���� Ȧ ������ ����
		if (flag4 == true)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 3.0f)
			{
				SceneManager::LoadScene(eSceneType::MainHall);
			}
		}

		switch (mPhase)
		{
		case ya::MantisLordsManager::ePhaseState::Phase1Start:
			phase1Start();
			break;

		case ya::MantisLordsManager::ePhaseState::Phase1:
			phase1();
			break;

		case ya::MantisLordsManager::ePhaseState::Phase2Start:
			phase2Start();
			break; 
		
		case ya::MantisLordsManager::ePhaseState::Phase2:
			phase2();
			break;

		case ya::MantisLordsManager::ePhaseState::Phase3:
			phase3();
			break;

		default:
			break;
		}
	}

	void MantisLordsManager::Release()
	{
		GameObject::Release();
	}

	void MantisLordsManager::phase1Start()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 2.0f)
		{
			mantisLord1->SetState(MantisLord1::eMantisLordsState::ThroneStand);
			mPhase = ePhaseState::Phase1;
			mTime = 0.0f;
			StartFlag1 = true;
		}
	}

	void MantisLordsManager::phase1()
	{
		// ���� 3���� �����ϰ� ����
		if (mantisLord1->GetState() == MantisLord1::eMantisLordsState::Idle)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				int pattern = rand() % 3;
				mTime = 0.0f;
				switch (pattern)
				{
				case 0:	// Dash
					mantisLord1->SetState(MantisLord1::eMantisLordsState::DashArrive);
					break;

				case 1:	// Dstab
					mantisLord1->SetState(MantisLord1::eMantisLordsState::DstabArrive);
					break;

				case 2:	// WallThrow
					mantisLord1->SetState(MantisLord1::eMantisLordsState::WallArrive);
					break;

				default:
					mantisLord1->SetState(MantisLord1::eMantisLordsState::Idle);
					break;
				}
			}
		}

		// 1�� ������ ������ 2������ ����
		if (mantisLord1->GetState() == MantisLord1::eMantisLordsState::ThroneWounded && StartFlag2 == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				mPhase = ePhaseState::Phase2Start;
				mTime = 0.0f;
				StartFlag2 = true;
			}
		}
	}

	void MantisLordsManager::phase2Start()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 2.0f)
		{
			mantisLord2->SetState(MantisLord2::eMantisLordsState::ThroneStand);
			mantisLord3->SetState(MantisLord3::eMantisLordsState::ThroneStand);
			mPhase = ePhaseState::Phase2;
			mTime = 0.0f;
			StartFlag2 = true;
		}
	}

	void MantisLordsManager::phase2()
	{
		// 2�� ������ ���� �ൿ �� 3�� ������ �����ؾ� ��
		
		// �� ������ ��� �������� ��� ���� ����
		if (mantisLord2->GetState() == MantisLord2::eMantisLordsState::Idle
			&& mantisLord3->GetState() == MantisLord3::eMantisLordsState::Idle)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				mTime = 0.0f;
				int pattern = rand() % 3;
				switch (pattern)
				{
				case 0:	// Dash
					mantisLord2->SetState(MantisLord2::eMantisLordsState::DashArrive);
					mantisLord3->SetState(MantisLord3::eMantisLordsState::DashArrive);
					break;

				case 1:	// Dstab
					mantisLord2->SetState(MantisLord2::eMantisLordsState::DstabArrive);
					mantisLord3->SetState(MantisLord3::eMantisLordsState::DstabArrive);
					break;

				case 2:	// WallThrow
					mantisLord2->SetState(MantisLord2::eMantisLordsState::WallArrive);
					mantisLord3->SetState(MantisLord3::eMantisLordsState::WallArrive);
					break;

				default:
					mantisLord2->SetState(MantisLord2::eMantisLordsState::Idle);
					mantisLord3->SetState(MantisLord3::eMantisLordsState::Idle);
					break;
				}
			}
		}

		// �� �� �ϳ��� ���� �� 3������ ����
		if (true)
		{

		}
	}

	void MantisLordsManager::phase3()
	{

	}
}