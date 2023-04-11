#include "Barb04.h"
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
	Vector2 Barb04PlayerPos;
	Vector2 Barb04PlayerDir;

	Barb04::Barb04()
	{
		tr = AddComponent<Transform>();
	}

	Barb04::~Barb04()
	{

	}

	void Barb04::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Thread\\Barb04", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Spike\\Barb04", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Loose\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Break\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Hornet_Barb ThreadBarb04") = std::bind(&Barb04::threadCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Looseneutral") = std::bind(&Barb04::looseCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Breakneutral") = std::bind(&Barb04::breakCompleteEvent, this);

		mState = eBarbState::Active;

		mCollider = AddComponent<Collider>();
		mCollider->SetActive(false);
		mCollider->SetSize(Vector2::Zero);

		GameObject::Initialize();
	}

	void Barb04::Update()
	{
		switch (mState)
		{
		case ya::Barb04::eBarbState::Disable:
			disable();
			break;

		case ya::Barb04::eBarbState::Active:
			active();
			break;

		case ya::Barb04::eBarbState::Thread:
			thread();
			break;

		case ya::Barb04::eBarbState::Spike:
			spike();
			break;

		case ya::Barb04::eBarbState::Loose:
			loose();
			break;

		case ya::Barb04::eBarbState::Break:
			barbBreak();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void Barb04::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Barb04::Release()
	{
		GameObject::Release();
	}

	void Barb04::OnCollisionEnter(Collider* other)
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
			Barb04PlayerPos = Player::GetInstance()->GetComponent<Collider>()->GetPos();	// 충돌시점 플레이어 pos
			//Barb04PlayerPos.y += 60.0f;
			Barb04PlayerDir = Barb04PlayerPos - mCollider->GetPos();
			Barb04PlayerDir = Barb04PlayerDir.Normalize();
			break;
		}
	}

	void Barb04::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb04::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb04::disable()
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

	void Barb04::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;
			this->SetState(eState::Active);

			// 초기 생성좌표
			tr->SetPos(Vector2(2100.0f, 1200.0f));

			mState = eBarbState::Thread;
		}
	}

	void Barb04::thread()
	{
		if (threadFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb ThreadBarb04", false);

			threadFlag = true;
		}
	}

	void Barb04::spike()
	{
		if (spikeFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb SpikeBarb04", false);

			mCollider->SetActive(true);
			mCollider->SetSize(Vector2(60.0f, 60.0f));
			mCollider->SetCenter(Vector2(-30.0f, -370.0f));

			spikeFlag = true;
		}

		// 일정 시간이 지나면 자연소멸
		mTime += Time::DeltaTime();
		if (mTime >= 8.0f)
		{
			mState = eBarbState::Loose;
		}
	}

	void Barb04::loose()
	{
		if (looseFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb Looseneutral", false);

			Vector2 pos = tr->GetPos();
			pos.y -= 320.0f;
			tr->SetPos(pos);

			mCollider->SetSize(Vector2::Zero);
			mCollider->SetActive(false);
			looseFlag = true;
		}

		if (hitFlag == true)
		{
			// 플레이어 방향으로 돌진
			Vector2 pos = tr->GetPos();
			pos.x -= SPEED * Barb04PlayerDir.x * Time::DeltaTime();
			pos.y -= SPEED * Barb04PlayerDir.y * Time::DeltaTime();
			tr->SetPos(pos);
		}
	}

	void Barb04::barbBreak()
	{
		if (breakFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb Breakneutral", false);

			breakFlag = true;
		}
	}

	void Barb04::threadCompleteEvent()
	{
		mState = eBarbState::Spike;
		threadFlag = false;
	}

	void Barb04::looseCompleteEvent()
	{
		mState = eBarbState::Break;
		looseFlag = false;
	}

	void Barb04::breakCompleteEvent()
	{
		mState = eBarbState::Disable;
		breakFlag = false;
	}
}