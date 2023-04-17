#include "MantisLord3.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaSound.h"

#include "yaPlayer.h"
#include "LongPlatform.h"

namespace ya
{
	MantisLord3* MantisLord3::instance = nullptr;

	MantisLord3::MantisLord3()
	{

	}

	MantisLord3::~MantisLord3()
	{

	}

	void MantisLord3::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		player = Player::GetInstance();

		//hp = 160;
		hp = 10;

		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Arrive\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Arrive\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Leave\\left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Leave\\right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Death\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Death Leave\\neutral", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Arrive\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Land\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Leave\\neutral", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Bow\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Idle\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Leave\\neutral", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Stand\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Wounded\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Gesture(Part 1)\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Gesture(Part 2)\\neutral", Vector2::Zero, 0.1f);
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

		landGroundSound = ResourceManager::Load<Sound>(L"MantisLords_LandonGround03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_Land on Ground.wav");
		jumpOfGroundSound = ResourceManager::Load<Sound>(L"MantisLordsJumpoffGround03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_jump off Ground.wav");
		dashSound = ResourceManager::Load<Sound>(L"MantisLordshorizontaldash03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_horizontal_dash.wav");
		landWallSound = ResourceManager::Load<Sound>(L"MantisLordslandcage03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_land_cage.wav");
		jumpOfWallSound = ResourceManager::Load<Sound>(L"MantisLordsjumpoffcage03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_jump_off_cage.wav");
		downSlashSound = ResourceManager::Load<Sound>(L"MantisLordsdownslash03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_down_slash.wav");
		downSlashImpactSound = ResourceManager::Load<Sound>(L"MantisLordsdownslashimpact03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_down_slash_impact.wav");
		downSlashArriveSound = ResourceManager::Load<Sound>(L"MantisLordsdstabarrive03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_dstab arrive.wav");
		wallSlashSound = ResourceManager::Load<Sound>(L"MantisLordswallattack03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis Lords_wall_attack.wav");
		deathSound = ResourceManager::Load<Sound>(L"MantisLorddeath03", L"..\\Resources\\Sound\\Mantis Lords\\Mantis_Lord_death_03.wav");
		damagedSound = ResourceManager::Load<Sound>(L"enemy_damaged", L"..\\Resources\\Sound\\enemy_damage.wav");

		mAnimator->Play(L"Mantis Lords_Throne Idleneutral", false);

		mCollider = AddComponent<Collider>();
		mCollider->SetActive(false);
		mCollider->SetCenter(Vector2(0.0f, 0.0f));
		mCollider->SetSize(Vector2(0.0f, 0.0f));

		mState = eMantisLordsState::ThroneIdle;

		GameObject::Initialize();
	}

	void MantisLord3::Update()
	{
		GameObject::Update();

		curScene = SceneManager::GetActiveScene();
		tr = GetComponent<Transform>();

		// 패턴 테스트용 코드
		if (Input::GetKeyDown(eKeyCode::I))
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

			mState = eMantisLordsState::DstabArrive;
			return;
		}

		// 사망시 옥좌로 귀환
		if (hp <= 0 && deathFlag == false)
		{
			mState = eMantisLordsState::Death;
		}

		// 플레이어 사망시 옥좌로 귀환
		if (mState == eMantisLordsState::Idle && player->GetPlayerState() == Player::ePlayerState::Death)
		{
			mState = eMantisLordsState::ThroneIdle;
		}

		switch (mState)
		{
		case ya::MantisLord3::eMantisLordsState::Idle:
			idle();
			break;

		case ya::MantisLord3::eMantisLordsState::ThroneIdle:
			throneIdle();
			break;

		case ya::MantisLord3::eMantisLordsState::ThroneStand:
			throneStand();
			break;

		case ya::MantisLord3::eMantisLordsState::ThroneBow:
			throneBow();
			break;

		case ya::MantisLord3::eMantisLordsState::ThroneLeave:
			throneLeave();
			break;

		case ya::MantisLord3::eMantisLordsState::ThroneWounded:
			throneWounded();
			break;

		case ya::MantisLord3::eMantisLordsState::Gesture1:
			gesture1();
			break;

		case ya::MantisLord3::eMantisLordsState::Gesture2:
			gesture2();
			break;

		case ya::MantisLord3::eMantisLordsState::DashArrive:
			dashArrive();
			break;

		case ya::MantisLord3::eMantisLordsState::DashAnticipate:
			dashAnticipate();
			break;

		case ya::MantisLord3::eMantisLordsState::Dash:
			dash();
			break;

		case ya::MantisLord3::eMantisLordsState::DashRecover:
			dashRecover();
			break;

		case ya::MantisLord3::eMantisLordsState::DashLeave:
			dashLeave();
			break;

		case ya::MantisLord3::eMantisLordsState::DstabArrive:
			dStabArrive();
			break;

		case ya::MantisLord3::eMantisLordsState::Dstab:
			dStab();
			break;

		case ya::MantisLord3::eMantisLordsState::DstabLand:
			dStabLand();
			break;

		case ya::MantisLord3::eMantisLordsState::DstabLeave:
			dStabLeave();
			break;

		case ya::MantisLord3::eMantisLordsState::WallArrive:
			wallArrive();
			break;

		case ya::MantisLord3::eMantisLordsState::WallReady:
			wallReady();
			break;

		case ya::MantisLord3::eMantisLordsState::WallLeave1:
			wallLeave1();
			break;

		case ya::MantisLord3::eMantisLordsState::WallLeave2:
			wallLeave2();
			break;

		case ya::MantisLord3::eMantisLordsState::Throw:
			wallThrow();
			break;

		case ya::MantisLord3::eMantisLordsState::Death:
			death();
			break;

		case ya::MantisLord3::eMantisLordsState::DeathLeave:
			deathLeave();
			break;

		default:
			break;
		}
	}

	void MantisLord3::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MantisLord3::Release()
	{
		GameObject::Release();
	}

	void MantisLord3::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		eLayerType otherType = other->GetOwner()->GetType();	// 오브젝트와 충돌한 객체의 타입
		if (mState != eMantisLordsState::Death)
		{
			switch (otherType)
			{
			case eLayerType::NeilEffect:
				hp -= Player::GetInstance()->GetNeilAtk();
				damagedSound->Play(false);
				break;

			case eLayerType::SpellEffect:
				hp -= Player::GetInstance()->GetSpellAtk();
				damagedSound->Play(false);
				break;
			}
		}
	}

	void MantisLord3::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void MantisLord3::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void MantisLord3::idle()
	{
		tr->SetPos(Vector2::Zero);
	}

	void MantisLord3::throneIdle()
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

	void MantisLord3::throneStand()
	{
		if (throneStandFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Throne Standneutral", false);
			throneStandFlag = true;
		}

		mTime += Time::DeltaTime();

		// 일어선지 3초 경과 후
		if (mTime >= 1.0f)
		{
			mState = eMantisLordsState::Gesture1;
			throneStandFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::throneBow()
	{
		if (throneBowFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Throne Bowneutral", false);
			throneBowFlag = true;
		}
	}

	void MantisLord3::throneLeave()
	{
		if (throneLeaveFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Throne Leaveneutral", false);
			throneLeaveFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.1f)
		{
			mState = eMantisLordsState::Idle;
			throneLeaveFlag = false;
		}
	}

	void MantisLord3::throneWounded()
	{
		if (throneWoundedFlag == false)
		{
			tr->SetPos(Vector2(1974.0f, 800.0f + 80.0f));

			mAnimator->Play(L"Mantis Lords_Throne Woundedneutral", false);
			throneWoundedFlag = true;
		}
	}

	void MantisLord3::gesture1()
	{
		if (gesture1Flag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.x += 13.0f;
			tr->SetPos(pos);

			mAnimator->Play(L"Mantis Lords_Gesture(Part 1)neutral", false);
			gesture1Flag = true;
		}



		mTime += Time::DeltaTime();

		// 
		if (mTime >= 1.0f)
		{
			mState = eMantisLordsState::Gesture2;
			gesture1Flag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::gesture2()
	{
		if (gesture2Flag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.x += 4.0f;
			tr->SetPos(pos);

			mAnimator->Play(L"Mantis Lords_Gesture(Part 2)neutral", false);
			gesture2Flag = true;
		}

		mTime += Time::DeltaTime();

		// 
		if (mTime >= 1.0f)
		{
			mState = eMantisLordsState::ThroneLeave;
			gesture2Flag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::dashArrive()
	{
		if (dashArriveFlag == false)
		{
			mCollider->SetActive(true);
			//int direction = rand() % 2;

			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-170.0f, -150.0f));
				mCollider->SetSize(Vector2(300.0f, 150.0f));
				landGroundSound->Play(false);
				tr->SetPos(Vector2(1200.0f + 1182.0f - 150.0f, 1300.0f - 103.0f));
				mAnimator->Play(L"Mantis Lords_Dash Arriveleft", false);
				dashArriveFlag = true;

				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(-130.0f, -150.0f));
				mCollider->SetSize(Vector2(300.0f, 150.0f));

				//mDirection = eDirection::Right;
				tr->SetPos(Vector2(1200.0f, 1300.0f - 103.0f));
				mAnimator->Play(L"Mantis Lords_Dash Arriveright", false);
				dashArriveFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.75f)
		{
			mState = eMantisLordsState::DashAnticipate;
			dashArriveFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::dashAnticipate()
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
		if (mTime >= 0.5f)
		{
			mState = eMantisLordsState::Dash;
			dashAnticipateFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLord3::dash()
	{
		if (dashFlag == false)
		{
			mCollider->SetCenter(Vector2(-200.0f, -150.0f));
			mCollider->SetSize(Vector2(400.0f, 150.0f));
			dashSound->Play(false);
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
			pos.x -= 5500.0f * Time::DeltaTime();

		else if (mDirection == eDirection::Right)
			pos.x += 5500.0f * Time::DeltaTime();

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

	void MantisLord3::dashRecover()
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
		if (mTime >= 1.0f)
		{
			mState = eMantisLordsState::DashLeave;
			dashRecoverFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLord3::dashLeave()
	{
		if (dashLeaveFlag == false)
		{
			mCollider->SetActive(false);
			Vector2 pos = tr->GetPos();
			jumpOfGroundSound->Play(false);
			switch (mDirection)
			{
			case eDirection::Left:	// left
				// 세부위치조정
				pos.x -= 20.0f;
				tr->SetPos(pos);
				mCollider->SetCenter(Vector2(0.0f, 0.0f));
				mCollider->SetSize(Vector2(0.0f, 0.0f));

				mAnimator->Play(L"Mantis Lords_Dash Leaveleft", false);
				dashLeaveFlag = true;

				break;

			case eDirection::Right:	// right
				// 세부위치조정
				pos.x += 20.0f;
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
		if (mTime >= 0.1f)
		{
			mState = eMantisLordsState::Idle;
			dashLeaveFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::wallArrive()
	{
		if (wallArriveFlag == false)
		{
			//int direction = rand() % 2;
			mCollider->SetActive(true);
			landWallSound->Play(false);
			switch (mDirection)
			{
			case eDirection::Left:	// left
				mCollider->SetCenter(Vector2(-300.0f, -550.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));
				tr->SetPos(Vector2(2200.0f - 1183.0f + 230.0f, 1100.0f));

				//mDirection = eDirection::Left;
				mAnimator->Play(L"Mantis Lords_Wall Arriveleft", false);
				wallArriveFlag = true;

				break;

			case eDirection::Right:	// right
				mCollider->SetCenter(Vector2(100.0f, -550.0f));
				mCollider->SetSize(Vector2(200.0f, 400.0f));
				tr->SetPos(Vector2(2200.0f, 1100.0f));

				//mDirection = eDirection::Right;
				mAnimator->Play(L"Mantis Lords_Wall Arriveright", false);
				wallArriveFlag = true;

				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.5f)
		{
			mState = eMantisLordsState::WallReady;
			wallArriveFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::wallReady()
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
		if (mTime >= 0.5f)
		{
			mState = eMantisLordsState::Throw;
			wallReadyFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::wallThrow()
	{
		if (throwFlag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.y -= 35.0f;
			tr->SetPos(pos);
			wallSlashSound->Play(false);
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
		if (mTime >= 1.5f)
		{
			mState = eMantisLordsState::WallLeave1;
			throwFlag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::wallLeave1()
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
		if (mTime >= 0.25f)
		{
			mState = eMantisLordsState::WallLeave2;
			wallLeave1Flag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::wallLeave2()
	{
		if (wallLeave2Flag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.y -= 100.0f;
			tr->SetPos(pos);
			jumpOfWallSound->Play(false);
			mCollider->SetActive(false);
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
		if (mTime >= 0.1f)
		{
			mState = eMantisLordsState::Idle;
			wallLeave2Flag = false;
			mTime = 0.0f;
			return;
		}
	}

	void MantisLord3::death()
	{
		if (deathFlag == false)
		{
			mCollider->SetActive(false);
			mCollider->SetCenter(Vector2(0.0f, 0.0f));
			mCollider->SetSize(Vector2(0.0f, 0.0f));
			deathSound->Play(false);
			mAnimator->Play(L"Mantis Lords_Deathneutral", false);
			deathFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 3.0f)
		{
			mState = eMantisLordsState::DeathLeave;
			mTime = 0.0f;
		}
	}

	void MantisLord3::deathLeave()
	{
		if (deathLeaveFlag == false)
		{
			mAnimator->Play(L"Mantis Lords_Death Leaveneutral", false);
			deathLeaveFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.2f)
		{
			mState = eMantisLordsState::ThroneWounded;
			mTime = 0.0f;
		}
	}

	void MantisLord3::dStabArrive()
	{
		if (dStabArriveFlag == false)
		{
			Vector2 pos = player->GetInstance()->GetPos();
			mCollider->SetCenter(Vector2(0.0f, -250.0f));
			mCollider->SetSize(Vector2(150.0f, 200.0f));
			mCollider->SetActive(true);
			downSlashArriveSound->Play(false);
			tr->SetPos(Vector2(pos.x, 800.0f));
			mAnimator->Play(L"Mantis Lords_Dstab Arriveneutral", false);
			dStabArriveFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 1.0f)
		{
			mState = eMantisLordsState::Dstab;
			dStabArriveFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLord3::dStab()
	{
		if (dStabFlag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.x += 30.0f;
			tr->SetPos(pos);

			mCollider->SetCenter(Vector2(-75.0f, -300.0f));
			mCollider->SetSize(Vector2(150.0f, 300.0f));
			downSlashSound->Play(false);
			mAnimator->Play(L"Mantis Lords_Dstabneutral", false);
			dStabFlag = true;
		}

		Vector2 pos = tr->GetPos();
		pos.y += 4300.0f * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime >= 0.1f)
		{
			mState = eMantisLordsState::DstabLand;
			dStabFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLord3::dStabLand()
	{
		if (dStabLandFlag == false)
		{
			// 세부위치조정
			Vector2 pos = tr->GetPos();
			pos.x -= 50.0f;
			pos.y = 1300.0f;
			tr->SetPos(pos);

			mCollider->SetCenter(Vector2(0.0f, -250.0f));
			mCollider->SetSize(Vector2(150.0f, 200.0f));
			downSlashImpactSound->Play(false);
			mAnimator->Play(L"Mantis Lords_Dstab Landneutral", false);
			dStabLandFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 1.0f)
		{
			mState = eMantisLordsState::DstabLeave;
			dStabLandFlag = false;
			mTime = 0.0f;

			return;
		}
	}

	void MantisLord3::dStabLeave()
	{
		if (dStabLeaveFlag == false)
		{
			mCollider->SetCenter(Vector2(0.0f, 0.0f));
			mCollider->SetSize(Vector2(0.0f, 0.0f));
			mCollider->SetActive(false);
			jumpOfGroundSound->Play(false);
			mAnimator->Play(L"Mantis Lords_Dstab Leaveneutral", false);
			dStabLeaveFlag = true;
		}

		Vector2 pos = tr->GetPos();
		pos.x += 2000.0f * Time::DeltaTime();
		pos.y -= 2000.0f * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime >= 0.1f)
		{
			mState = eMantisLordsState::Idle;
			dStabLeaveFlag = false;
			mTime = 0.0f;

			return;
		}
	}
}