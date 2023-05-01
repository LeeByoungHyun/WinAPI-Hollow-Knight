#include "HPobject04.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaTransform.h"

namespace ya
{
	// ΩÃ±€≈Ê ∞¥√º √ ±‚»≠
	HPobject04* HPobject04::instance = nullptr;

	HPobject04::HPobject04()
	{

	}

	HPobject04::~HPobject04()
	{

	}

	void HPobject04::Initialize()
	{
		GameObject::Initialize();

		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\001.Health Empty", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\002.Health Idle", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\003.Health Break", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\004.Health Refill", Vector2::Zero, 0.066f);

		mAnimator->GetCompleteEvent(L"Health003.Health Break") = std::bind(&HPobject04::breakHPCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Health004.Health Refill") = std::bind(&HPobject04::reFillCompleteEvent, this);

		tr->SetPos(Vector2(270.0f, 70.0f));
		tr->SetSize(Vector2(0.5f, 0.5f));

		mAnimator->Play(L"Health002.Health Idle", true);
		mAnimator->setUseCamera(false);

		mHPstate = eHPState::Idle;
	}

	void HPobject04::Update()
	{
		GameObject::Update();

		activeScene = SceneManager::GetActiveScene();

		switch (mHPstate)
		{
		case ya::HPobject04::eHPState::Empty:
			empty();
			break;
		case ya::HPobject04::eHPState::Idle:
			idle();
			break;
		case ya::HPobject04::eHPState::Break:
			breakHp();
			break;
		case ya::HPobject04::eHPState::Refiil:
			reFill();
			break;
		default:
			break;
		}
	}

	void HPobject04::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HPobject04::Release()
	{
		GameObject::Release();
	}

	void HPobject04::initializeFlag()
	{
		emptyFlag = false;
		idleFlag = false;
		breakHpFlag = false;
		reFillFlag = false;
	}

	void HPobject04::empty()
	{
		if (emptyFlag == false)
		{
			emptyFlag = true;
			reFillFlag = false;
			mAnimator->Play(L"Health001.Health Empty", false);

			Vector2 pos = tr->GetPos();

			if (breakHpFlag == true)
			{
				breakHpFlag = false;
				pos.x += 2.5f;
				pos.y += 19.0f;
			}

			pos.y -= 14.0f;
			tr->SetPos(Vector2(270.0f, 70.0f - 14.0f));
		}
	}
	void HPobject04::idle()
	{
		if (idleFlag == false)
		{
			idleFlag = true;
			mAnimator->Play(L"Health002.Health Idle", true);

			Vector2 pos = tr->GetPos();

			if (reFillFlag == true)
			{
				pos.x += 15.5f;
				pos.y += 15.0f;
				reFillFlag == false;
			}

			tr->SetPos(Vector2(270.0f, 70.0f));
		}
	}
	void HPobject04::breakHp()
	{
		if (breakHpFlag == false)
		{
			breakHpFlag = true;
			idleFlag = false;
			mAnimator->Play(L"Health003.Health Break", false);

			Vector2 pos = tr->GetPos();
			pos.x -= 2.5f;
			pos.y -= 19.0f;
			tr->SetPos(Vector2(270.0f - 2.5f, 70.0f - 19.0f));

		}
	}
	void HPobject04::reFill()
	{
		if (reFillFlag == false)
		{
			reFillFlag = true;
			emptyFlag = false;
			mAnimator->Play(L"Health004.Health Refill", false);

			Vector2 pos = tr->GetPos();
			pos.y += 14.0f;
			pos.x -= 15.5f;
			pos.y -= 15.0f;
			tr->SetPos(Vector2(270.0f - 15.0f, 70.0f - 15.0f));
		}
	}

	void HPobject04::breakHPCompleteEvent()
	{
		mHPstate = eHPState::Empty;
	}

	void HPobject04::reFillCompleteEvent()
	{
		mHPstate = eHPState::Idle;
	}
}

