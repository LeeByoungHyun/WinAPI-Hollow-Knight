#include "Barb.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaRigidBody.h"

#include "Hornet.h"
#include "yaPlayer.h"

namespace ya
{
	Vector2 playerPos;
	Vector2 playerDir;

	const float SPEED = 800.0f;

	Barb::Barb()
	{
		tr = AddComponent<Transform>();
	}

	Barb::~Barb()
	{

	}

	void Barb::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Thread\\Barb01", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Spike\\Barb01", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Loose\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Break\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Hornet_Barb ThreadBarb01") = std::bind(&Barb::threadCompleteEvent, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetActive(false);

		GameObject::Initialize();
	}

	void Barb::Update()
	{
		switch (mState)
		{
		case ya::Barb::eBarbState::Disable:
			disable();
			break;

		case ya::Barb::eBarbState::Active:
			active();
			break;

		case ya::Barb::eBarbState::Thread:
			thread();
			break;

		case ya::Barb::eBarbState::Spike:
			spike();
			break;

		case ya::Barb::eBarbState::Loose:
			loose();
			break;

		case ya::Barb::eBarbState::Break:
			barbBreak();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void Barb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Barb::Release()
	{
		GameObject::Release();
	}

	void Barb::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		

		eLayerType otherType = other->GetOwner()->GetType();	// 충돌한 객체의 타입
		switch (otherType)
		{
			// 플레이어의 공격일 경우
		case eLayerType::NeilEffect:
			mState = eBarbState::Loose;
			hitFlag = true;

			// 플레이어 공격과 충돌하면 반대방향으로 튕겨나감
			playerPos = Player::GetInstance()->GetComponent<Transform>()->GetPos();	// 충돌시점 플레이어 pos
			playerDir = playerPos - tr->GetPos();
			playerDir = playerDir.Normalize();
			break;
		}
	}

	void Barb::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			this->SetState(eState::Pause);
		}
	}

	void Barb::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;
			this->SetState(eState::Active);

			// 초기 생성좌표
			tr->SetPos(Vector2(0.0f, 0.0f));

			mState = eBarbState::Thread;
		}
	}

	void Barb::thread()
	{
		if (threadFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb ThreadBarb01", false);

			threadFlag = true;
		}
	}

	void Barb::spike()
	{
		if (spikeFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb SpikeBarb01", false);

			mCollider->SetActive(true);
			mCollider->SetSize(Vector2(60.0f, 60.0f));
			mCollider->SetCenter(Vector2(0.0f, 0.0f));

			spikeFlag = true;
		}

		// 일정 시간이 지나면 자연소멸
		mTime += Time::DeltaTime();
		if (mTime >= 8.0f)
		{
			mState = eBarbState::Loose;
		}
	}

	void Barb::loose()
	{
		if (looseFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb LooseBarb01", false);

			looseFlag = true;
		}

		if (hitFlag == true)
		{
			// 플레이어 방향으로 돌진
			Vector2 pos = tr->GetPos();
			pos.x -= SPEED * playerDir.x * Time::DeltaTime();
			pos.y -= SPEED * playerDir.y * Time::DeltaTime();
			tr->SetPos(pos);
		}
	}

	void Barb::barbBreak()
	{
		if (breakFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb BreakBarb01", false);

			breakFlag = true;
		}
	}

	void Barb::threadCompleteEvent()
	{
		mState = eBarbState::Spike;
		threadFlag = false;
	}

	void Barb::looseCompleteEvent()
	{
		mState = eBarbState::Break;
		looseFlag = false;
	}
}