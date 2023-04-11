#include "Barb03.h"
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
	Vector2 Barb03PlayerPos;
	Vector2 Barb03PlayerDir;

	Barb03::Barb03()
	{
		tr = AddComponent<Transform>();
	}

	Barb03::~Barb03()
	{

	}

	void Barb03::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Thread\\Barb03", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Spike\\Barb03", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Loose\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Barb Break\\neutral", Vector2::Zero, 0.1f);

		mAnimator->GetCompleteEvent(L"Hornet_Barb ThreadBarb03") = std::bind(&Barb03::threadCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Looseneutral") = std::bind(&Barb03::looseCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Hornet_Barb Breakneutral") = std::bind(&Barb03::breakCompleteEvent, this);

		mState = eBarbState::Active;

		mCollider = AddComponent<Collider>();
		mCollider->SetActive(false);
		mCollider->SetSize(Vector2::Zero);

		GameObject::Initialize();
	}

	void Barb03::Update()
	{
		switch (mState)
		{
		case ya::Barb03::eBarbState::Disable:
			disable();
			break;

		case ya::Barb03::eBarbState::Active:
			active();
			break;

		case ya::Barb03::eBarbState::Thread:
			thread();
			break;

		case ya::Barb03::eBarbState::Spike:
			spike();
			break;

		case ya::Barb03::eBarbState::Loose:
			loose();
			break;

		case ya::Barb03::eBarbState::Break:
			barbBreak();
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void Barb03::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Barb03::Release()
	{
		GameObject::Release();
	}

	void Barb03::OnCollisionEnter(Collider* other)
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
			Barb03PlayerPos = Player::GetInstance()->GetComponent<Collider>()->GetPos();	// 충돌시점 플레이어 pos
			//Barb03PlayerPos.y += 60.0f;
			Barb03PlayerDir = Barb03PlayerPos - mCollider->GetPos();
			Barb03PlayerDir = Barb03PlayerDir.Normalize();
			break;
		}
	}

	void Barb03::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb03::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Barb03::disable()
	{
		if (disableFlag == false)
		{
			activeFlag = false;
			disableFlag = true;

			tr->SetPos(Vector2::Zero);
			mCollider->SetSize(Vector2::Zero);

			threadFlag = false;
			spikeFlag = false;
			looseFlag = false;
			breakFlag = false;
			hitFlag = false;
			//this->SetState(eState::Pause);
		}
	}

	void Barb03::active()
	{
		if (activeFlag == false)
		{
			disableFlag = false;
			activeFlag = true;
			//this->SetState(eState::Active);

			// 초기 생성좌표
			tr->SetPos(Vector2(1700.0f, 1000.0f));

			mState = eBarbState::Thread;
		}
	}

	void Barb03::thread()
	{
		if (threadFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb ThreadBarb03", false);

			threadFlag = true;
		}
	}

	void Barb03::spike()
	{
		if (spikeFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb SpikeBarb03", false);

			mCollider->SetActive(true);
			mCollider->SetSize(Vector2(60.0f, 60.0f));
			mCollider->SetCenter(Vector2(-20.0f, -330.0f));

			spikeFlag = true;
		}

		// 일정 시간이 지나면 자연소멸
		/*
		mTime += Time::DeltaTime();
		if (mTime >= 8.0f)
		{
			mState = eBarbState::Loose;
		}
		*/
	}

	void Barb03::loose()
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
			Vector2 pos = tr->GetPos();
			pos.x -= SPEED * Barb03PlayerDir.x * Time::DeltaTime();
			pos.y -= SPEED * Barb03PlayerDir.y * Time::DeltaTime();
			tr->SetPos(pos);
		}
	}

	void Barb03::barbBreak()
	{
		if (breakFlag == false)
		{
			mAnimator->Play(L"Hornet_Barb Breakneutral", false);

			breakFlag = true;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.3f)
		{
			mTime = 0.0f;
			mState = eBarbState::Disable;
			breakFlag = false;
		}
	}

	void Barb03::threadCompleteEvent()
	{
		mState = eBarbState::Spike;
		threadFlag = false;
	}

	void Barb03::looseCompleteEvent()
	{
		mState = eBarbState::Break;
		looseFlag = false;
	}

	void Barb03::breakCompleteEvent()
	{
		//mState = eBarbState::Disable;
		//breakFlag = false;
	}
}