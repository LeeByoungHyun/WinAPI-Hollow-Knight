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

		// �÷��̾ ������ ���� �� 1�� �������� ����
		if (activeScene->GetType() == eSceneType::MantisLordsBoss && StartFlag1 == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				mantisLord1->SetState(MantisLord1::eMantisLordsState::ThroneStand);
				mTime = 0.0f;
				StartFlag1 = true;
			}
		}

		// 1�� ������ ������ 2, 3�� ���� ���ÿ� ����
		if (mantisLord1->GetState() == MantisLord1::eMantisLordsState::ThroneWounded && StartFlag2 == false)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				mantisLord2->SetState(MantisLord2::eMantisLordsState::ThroneStand);
				mantisLord3->SetState(MantisLord3::eMantisLordsState::ThroneStand);
				mTime = 0.0f;
				StartFlag2 = true;
			}
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

		// 2, 3�� ������ ���ÿ� �����̰� ������ ���⿡�� ���� ����
		// �� �� �ϳ��� ������ �ٽ� 1�� ����ó�� ������
		if (StartFlag2 == true && startFlag3 == false)
		{

		}
	}

	void MantisLordsManager::Release()
	{
		GameObject::Release();

	}
}