#include "Barb02.h"
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
	Vector2 Barb02PlayerPos;
	Vector2 Barb02PlayerDir;

	Barb02::Barb02()
	{
		tr = AddComponent<Transform>();
	}

	Barb02::~Barb02()
	{

	}

	void Barb02::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Thread\\Barb02", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Spike\\Barb02", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Loose\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Break\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Hornet_Barb ThreadBarb02") = std::bind(&Barb02::threadCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Looseneutral") = std::bind(&Barb02::looseCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Breakneutral") = std::bind(&Barb02::breakCompleteEvent, this);

		mState = eBarbState::Active;

		mCollider = AddComponent<Collider>();
		mCollider->SetActive(false);
		mCollider->SetSize(Vector2::Zero);

		GameObject::Initialize();
	}

	void Barb02::Update()
	{
		switch (mState)
		{
		case ya::Barb02::eBarbState::Disable:
			disable();
			break;

		case ya::Barb02::eBarbState::Active:
			active();
			break;

		case ya::Barb02::eBarbState::Thread:
			thread();
			break;

		case ya::Barb02::eBarbState::Spike:
			spike();
			break;

		case ya::Barb02::eBarbState::Loose:
			loose();
			break;

		case ya::Barb02::eBarbState::Break:
			barbBreak();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void Barb02::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Barb02::Release()
	{
		GameObject::Release();
	}

	void Barb02::OnCollisionEnter(Collider* other)
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
			Barb02PlayerPos = Player::GetInstance()->GetComponent<Collider>()->GetPos();	// 충돌시점 플레이어 pos
			//Barb02PlayerPos.y += 60.0f;
			Barb02PlayerDir = Barb02PlayerPos - mCollider->GetPos();
			Barb02PlayerDir = Barb02PlayerDir.Normalize();
			break;
		}
	}

	void Barb02::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb02::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb02::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			this->SetState(eState::Pause);
			mCollider->SetSize(Vector2::Zero);

		}
	}

	void Barb02::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;
			this->SetState(eState::Active);

			// 초기 생성좌표
			tr->SetPos(Vector2(1600.0f, 1200.0f));

			mState = eBarbState::Thread;
		}
	}

	void Barb02::thread()
	{
		if (threadFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb ThreadBarb02", false);

			threadFlag = true;
		}
	}

	void Barb02::spike()
	{
		if (spikeFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb SpikeBarb02", false);

			mCollider->SetActive(true);
			mCollider->SetSize(Vector2(60.0f, 60.0f));
			mCollider->SetCenter(Vector2(-20.0f, -220.0f));

			spikeFlag = true;
		}

		// 일정 시간이 지나면 자연소멸
		mTime += Time::DeltaTime();
		if (mTime >= 8.0f)
		{
			mState = eBarbState::Loose;
		}
	}

	void Barb02::loose()
	{
		if (looseFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb Looseneutral", false);

			Vector2 pos = tr->GetPos();
			pos.y -= 190.0f;
			tr->SetPos(pos);

			mCollider->SetSize(Vector2::Zero);
			mCollider->SetActive(false);
			looseFlag = true;
		}

		if (hitFlag == true)
		{
			// 플레이어 방향으로 돌진
			Vector2 pos = tr->GetPos();
			pos.x -= SPEED * Barb02PlayerDir.x * Time::DeltaTime();
			pos.y -= SPEED * Barb02PlayerDir.y * Time::DeltaTime();
			tr->SetPos(pos);
		}
	}

	void Barb02::barbBreak()
	{
		if (breakFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb Breakneutral", false);

			breakFlag = true;
		}
	}

	void Barb02::threadCompleteEvent()
	{
		mState = eBarbState::Spike;
		threadFlag = false;
	}

	void Barb02::looseCompleteEvent()
	{
		mState = eBarbState::Break;
		looseFlag = false;
	}

	void Barb02::breakCompleteEvent()
	{
		mState = eBarbState::Disable;
		breakFlag = false;
	}
}