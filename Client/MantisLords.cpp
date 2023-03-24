#include "MantisLords.h"
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
	MantisLords::MantisLords()
	{

	}

	MantisLords::~MantisLords()
	{

	}

	void MantisLords::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		player = Player::GetInstance();

		hp = 100;

		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Arrive\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Arrive\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Leave\\left", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Leave\\right", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Recover)\\right", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Death\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Death Leave\\neutral", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Arrive\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Land\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Leave\\neutral", Vector2::Zero, 0.02f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Bow\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Idle\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Leave\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Stand\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Wounded\\neutral", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throw\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throw\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Arrive\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Arrive\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 1)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 1)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 2)\\left", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 2)\\right", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Ready\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Ready\\right", Vector2::Zero, 0.1f);

		mAnimator->Play(L"Mantis Lords_Throne Idleneutral", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetName(L"MantisLordCollider");
		mCollider->SetCenter(Vector2(-50.0f, -300.0f));
		mCollider->SetSize(Vector2(100.0f, 300.0f));

		mState = eMantisLordsState::ThroneIdle;

		GameObject::Initialize();
	}

	void MantisLords::Update()
	{
		GameObject::Update();

		curScene = SceneManager::GetActiveScene();
		tr = GetComponent<Transform>();

		// 테스트
		if (Input::GetKeyDown(eKeyCode::O))
		{
			throneStandFlag = false;
			throneBowFlag = false;
			throneLeaveFlag = false;
			throneWoundedFlag = false;
			dashArriveFlag = false;
			dashAnticipateFlag = false;
			dashFlag = false;
			dashRecoverFlag = false;
			dashLeaveFlag = false;
			dStabArriveFlag = false;
			dStabFlag = false;
			dStabLandFlag = false;
			dStabLeaveFlag = false;
			wallArriveFlag = false;
			wallReadyFlag = false;
			throwFlag = false;
			wallLeave1Flag = false;
			wallLeave2Flag = false;

			mState = eMantisLordsState::DashArrive;
			return;
		}

		// 플레이어 사망시 옥좌로 귀환
		if (mState == eMantisLordsState::Idle && player->GetPlayerState() == Player::ePlayerState::Death)
		{
			mState = eMantisLordsState::ThroneIdle;
		}

		switch (mState)
		{
		case ya::MantisLords::eMantisLordsState::Idle:
			idle();
			break;

		case ya::MantisLords::eMantisLordsState::ThroneIdle:
			throneIdle();
			break;

		case ya::MantisLords::eMantisLordsState::ThroneStand:
			throneStand();
			break;

		case ya::MantisLords::eMantisLordsState::ThroneBow:
			throneBow();
			break;

		case ya::MantisLords::eMantisLordsState::ThroneLeave:
			throneLeave();
			break;

		case ya::MantisLords::eMantisLordsState::ThroneWounded:
			throneWounded();
			break;

		case ya::MantisLords::eMantisLordsState::DashArrive:
			dashArrive();
			break;

		case ya::MantisLords::eMantisLordsState::DashAnticipate:
			dashAnticipate();
			break;

		case ya::MantisLords::eMantisLordsState::Dash:
			dash();
			break;

		case ya::MantisLords::eMantisLordsState::DashRecover:
			dashRecover();
			break;

		case ya::MantisLords::eMantisLordsState::DashLeave:
			dashLeave();
			break;

		case ya::MantisLords::eMantisLordsState::DstabArrive:
			dStabArrive();
			break;

		case ya::MantisLords::eMantisLordsState::Dstab:
			dStab();
			break;

		case ya::MantisLords::eMantisLordsState::DstabLand:
			dStabLand();
			break;

		case ya::MantisLords::eMantisLordsState::DstabLeave:
			dStabLeave();
			break;

		case ya::MantisLords::eMantisLordsState::WallArrive:
			wallArrive();
			break;

		case ya::MantisLords::eMantisLordsState::WallReady:
			wallReady();
			break;

		case ya::MantisLords::eMantisLordsState::WallLeave1:
			wallLeave1();
			break;

		case ya::MantisLords::eMantisLordsState::WallLeave2:
			wallLeave2();
			break;

		case ya::MantisLords::eMantisLordsState::Throw:
			wallThrow();
			break;

		default:
			break;
		}
	}

	void MantisLords::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MantisLords::Release()
	{
		GameObject::Release();
	}

	void MantisLords::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void MantisLords::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void MantisLords::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void MantisLords::idle()
	{
		tr->SetPos(Vector2::Zero);
		//mAnimator->Play(L"", false);

		mTime += Time::DeltaTime();
		if (mTime >= 1.0f)
		{
			// 각 패턴이 종료되면 돌아오는 준비상태
			// 패턴 끝나고 약 1초 뒤 다음 패턴 시작
			// 랜덤 함수 이용해 패턴 랜덤하게 호출
			int pattern = rand() % 3;
			switch (pattern)
			{
			case 0:	// Dash
				mState = eMantisLordsState::DashArrive;
				break;

			case 1:	// Dstab
				mState = eMantisLordsState::DstabArrive;
				break;

			case 2:	// WallThrow
				mState = eMantisLordsState::WallArrive;
				break;

			default:
				mState = eMantisLordsState::Idle;
				break;
			}
		}
	}

	void MantisLords::throneIdle()
	{
		mAnimator->Play(L"Mantis Lords_Throne Idleneutral", true);
		// O입력시 일어남
		// 임시
		// 테스트 끝나면 보스룸 입장 후 일정 시간이 지나면 일어서게끔 수정할것
		if (Input::GetKeyDown(eKeyCode::O))
		{
			mState = eMantisLordsState::ThroneStand;
			return;
		}
	}

	void MantisLords::throneStand()
	{
		if (throneStandFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Throne Standneutral", false);
			throneStandFlag = true;
		}

		mTime += Time::DeltaTime();

		// 일어선지 3초 경과 후
		if (mTime >= 2.0f)
		{
			mState = eMantisLordsState::ThroneLeave;
			throneStandFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::throneBow()
	{
		if (throneBowFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Throne Bowneutral", false);
			throneBowFlag = true;
		}
	}

	void MantisLords::throneLeave()
	{
		if (throneLeaveFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Throne Leaveneutral", false);
			throneLeaveFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 1.0f)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 1.0f)
			{
				// 각 패턴이 종료되면 돌아오는 준비상태
				// 패턴 끝나고 약 1초 뒤 다음 패턴 시작
				// 랜덤 함수 이용해 패턴 랜덤하게 호출
				int pattern = rand() % 3;
				switch (pattern)
				{
				case 0:	// Dash
					mState = eMantisLordsState::DashArrive;
					break;

				case 1:	// Dstab
					mState = eMantisLordsState::DstabArrive;
					break;

				case 2:	// WallThrow
					mState = eMantisLordsState::WallArrive;
					break;

				default:
					mState = eMantisLordsState::Idle;
					break;
				}
			}
		}
	}

	void MantisLords::throneWounded()
	{
		if (throneBowFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Throne Woundedneutral", false);
			throneBowFlag = true;
		}
	}

	void MantisLords::dashArrive()
	{
		if (dashArriveFlag == false)
		{
			int direction = rand() % 2;
			switch (direction)
			{
			case 0:	// left
				mCollider->SetCenter(Vector2(-170.0f, -150.0f));
				mCollider->SetSize(Vector2(300.0f, 150.0f));

				mDirection = eDirection::Left;
				tr->SetPos(Vector2(2200.0f, 1300.0f - 103.0f));
				mAnimator->Play(L"Mantis Lords_Dash Arriveleft", false);
				dashArriveFlag = true;

				break;

			case 1:	// right
				mCollider->SetCenter(Vector2(-130.0f, -150.0f));
				mCollider->SetSize(Vector2(300.0f, 150.0f));

				mDirection = eDirection::Right;
				tr->SetPos(Vector2(2200.0f - 1183.0f, 1300.0f - 103.0f));
				mAnimator->Play(L"Mantis Lords_Dash Arriveright", false);
				dashArriveFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::DashAnticipate;
			dashArriveFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::dashAnticipate()
	{
		if (dashAnticipateFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-90.0f, -300.0f));
				mCollider->SetSize(Vector2(160.0f, 300.0f));

				mAnimator->Play(L"Mantis Lords_Dash(Anticipate)left", false);
				dashAnticipateFlag = true;

				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-70.0f, -300.0f));
				mCollider->SetSize(Vector2(160.0f, 300.0f));

				mAnimator->Play(L"Mantis Lords_Dash(Anticipate)right", false);
				dashAnticipateFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::Dash;
			dashAnticipateFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLords::dash()
	{
		if (dashFlag == false)
		{
			mCollider->SetCenter(Vector2(-200.0f, -150.0f));
			mCollider->SetSize(Vector2(400.0f, 150.0f));

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Mantis Lords_Dashleft", false);
				dashFlag = true;

				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Mantis Lords_Dashright", false);
				dashFlag = true;

				break;

			default:
				break;
			}
		}

		Vector2 pos = tr->GetPos();

		if (mDirection == eDirection::Left)
			pos.x -= 6000.0f * Time::DeltaTime();

		else if (mDirection == eDirection::Right)
			pos.x += 6000.0f * Time::DeltaTime();

		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime >= 0.2f)
		{
			mState = eMantisLordsState::DashRecover;
			dashFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLords::dashRecover()
	{
		if (dashRecoverFlag == false)
		{
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-50.0f, -150.0f));
				mCollider->SetSize(Vector2(300.0f, 150.0f));

				mAnimator->Play(L"Mantis Lords_Dash(Recover)left", false);
				dashRecoverFlag = true;

				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-250.0f, -150.0f));
				mCollider->SetSize(Vector2(300.0f, 150.0f));

				mAnimator->Play(L"Mantis Lords_Dash(Recover)right", false);
				dashRecoverFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::DashLeave;
			dashRecoverFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLords::dashLeave()
	{
		if (dashLeaveFlag == false)
		{
			Vector2 pos = tr->GetPos();

			switch (mDirection)
			{
			case eDirection::Left:	// left
				// 세부위치조정
				pos.x -= 30.0f;
				tr->SetPos(pos);
				mCollider->SetCenter(Vector2(0.0f, 0.0f));
				mCollider->SetSize(Vector2(0.0f, 0.0f));

				mAnimator->Play(L"Mantis Lords_Dash Leaveleft", false);
				dashLeaveFlag = true;

				break;

			case eDirection::Right:	// right
				// 세부위치조정
				pos.x += 30.0f;
				tr->SetPos(pos);
				mCollider->SetCenter(Vector2(0.0f, 0.0f));
				mCollider->SetSize(Vector2(0.0f, 0.0f));

				mAnimator->Play(L"Mantis Lords_Dash Leaveright", false);
				dashLeaveFlag = true;

				break;

			default:
				break;
			}
		}

		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Left)
		{
			pos.x -= 2000.0f * Time::DeltaTime();
			pos.y -= 2000.0f * Time::DeltaTime();
		}
			
		else if (mDirection == eDirection::Right)
		{
			pos.x += 2000.0f * Time::DeltaTime();
			pos.y -= 2000.0f * Time::DeltaTime();
		}

		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime >= 0.1)
		{
			mState = eMantisLordsState::Idle;
			dashLeaveFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::wallArrive()
	{
		if (wallArriveFlag == false)
		{
			int direction = rand() % 2;

			switch (direction)
			{
			case 0:	// left
				mCollider->SetCenter(Vector2(-300.0f, -550.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));
				tr->SetPos(Vector2(2200.0f - 1183.0f, 1100.0f));

				mDirection = eDirection::Left;
				mAnimator->Play(L"Mantis Lords_Wall Arriveleft", false);
				wallArriveFlag = true;

				break;

			case 1:	// right
				mCollider->SetCenter(Vector2(100.0f, -550.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));
				tr->SetPos(Vector2(2200.0f, 1100.0f));

				mDirection = eDirection::Right;
				mAnimator->Play(L"Mantis Lords_Wall Arriveright", false);
				wallArriveFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::WallReady;
			wallArriveFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::wallReady()
	{
		if (wallReadyFlag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.y += 30.0f;
			tr->SetPos(pos);

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-300.0f, -580.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));

				mAnimator->Play(L"Mantis Lords_Wall Readyleft", false);
				wallReadyFlag = true;

				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(100.0f, -580.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));

				mAnimator->Play(L"Mantis Lords_Wall Readyright", false);
				wallReadyFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::Throw;
			wallReadyFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::wallThrow()
	{
		if (throwFlag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.y -= 35.0f;
			tr->SetPos(pos);

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-300.0f, -545.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));

				mAnimator->Play(L"Mantis Lords_Throwleft", false);
				throwFlag = true;

				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(100.0f, -545.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));

				mAnimator->Play(L"Mantis Lords_Throwright", false);
				throwFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::WallLeave1;
			throwFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::wallLeave1()
	{
		if (wallLeave1Flag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.y -= 35.0f;
			tr->SetPos(pos);

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-300.0f, -510.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));

				mAnimator->Play(L"Mantis Lords_Wall Leave(Part 1)left", false);
				wallLeave1Flag = true;

				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(100.0f, -510.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));

				mAnimator->Play(L"Mantis Lords_Wall Leave(Part 1)right", false);
				wallLeave1Flag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::WallLeave2;
			wallLeave1Flag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::wallLeave2()
	{
		if (wallLeave2Flag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.y -= 100.0f;
			tr->SetPos(pos);

			mCollider->SetCenter(Vector2(0.0f, 0.0f));
			mCollider->SetSize(Vector2(0.0f, 0.0f));

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mAnimator->Play(L"Mantis Lords_Wall Leave(Part 2)left", false);
				wallLeave2Flag = true;

				break;

			case eDirection::Right:	// right
				mAnimator->Play(L"Mantis Lords_Wall Leave(Part 2)right", false);
				wallLeave2Flag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.1)
		{
			mState = eMantisLordsState::Idle;
			wallLeave2Flag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLords::death()
	{
	}

	void MantisLords::deathLeave()
	{
	}

	void MantisLords::dStabArrive()
	{
		if (dStabArriveFlag == false)
		{
			Vector2 pos = player->GetInstance()->GetPos();
			mCollider->SetCenter(Vector2(0.0f, -250.0f));
			mCollider->SetSize(Vector2(150.0f, 200.0f));

			// 플레이어 x좌표 위에 생성되야 함 지금은 임시
			tr->SetPos(Vector2(pos.x, 650.0f));
			mAnimator->Play(L"Mantis Lords_Dstab Arriveneutral", false);
			dStabArriveFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 1.0)
		{
			mState = eMantisLordsState::Dstab;
			dStabArriveFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLords::dStab()
	{
		if (dStabFlag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.x += 30.0f;
			tr->SetPos(pos);

			mCollider->SetCenter(Vector2(-75.0f, -300.0f));
			mCollider->SetSize(Vector2(150.0f, 300.0f));

			mAnimator->Play(L"Mantis Lords_Dstabneutral", false);
			dStabFlag = true;
		}

		Vector2 pos = tr->GetPos();
		pos.y += 6000.0f * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime >= 0.1)
		{
			mState = eMantisLordsState::DstabLand;
			dStabFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLords::dStabLand()
	{
		if (dStabLandFlag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			tr->SetPos(pos);

			mCollider->SetCenter(Vector2(0.0f, -250.0f));
			mCollider->SetSize(Vector2(150.0f, 200.0f));

			mAnimator->Play(L"Mantis Lords_Dstab Landneutral", false);
			dStabLandFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5)
		{
			mState = eMantisLordsState::DstabLeave;
			dStabLandFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLords::dStabLeave()
	{
		if (dStabLeaveFlag == false)
		{
			mCollider->SetCenter(Vector2(0.0f, 0.0f));
			mCollider->SetSize(Vector2(0.0f, 0.0f));

			mAnimator->Play(L"Mantis Lords_Dstab Leaveneutral", false);
			dStabLeaveFlag = true;
		}

		Vector2 pos = tr->GetPos();
		pos.x += 2000.0f * Time::DeltaTime();
		pos.y -= 2000.0f * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime >= 0.1)
		{
			mState = eMantisLordsState::Idle;
			dStabLeaveFlag = false;
			mTime = 0.0f;

			return;
		}
	}
}