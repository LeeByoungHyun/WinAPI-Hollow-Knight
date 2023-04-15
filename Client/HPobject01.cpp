#include "HPobject01.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaTransform.h"
#include "yaCamera.h"

namespace ya
{
	// ΩÃ±€≈Ê ∞¥√º √ ±‚»≠
	HPobject01* HPobject01::instance = nullptr;

	HPobject01::HPobject01()
	{

	}

	HPobject01::~HPobject01()
	{

	}

	void HPobject01::Initialize()
	{
		GameObject::Initialize();

		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\001.Health Empty", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\002.Health Idle", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\003.Health Break", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\004.Health Refill", Vector2::Zero, 0.066f);

		mAnimator->GetCompleteEvent(L"Health003.Health Break") = std::bind(&HPobject01::breakHPCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Health004.Health Refill") = std::bind(&HPobject01::reFillCompleteEvent, this);

		mAnimator->Play(L"Health002.Health Idle", true);
		mAnimator->setUseCamera(false);

		tr->SetPos(Vector2(150.0f, 70.0f));
		tr->SetSize(Vector2(0.5f, 0.5f));

		mHPstate = eHPState::Idle;
	}

	void HPobject01::Update()
	{
		GameObject::Update();

		activeScene = SceneManager::GetActiveScene();

		switch (mHPstate)
		{
		case ya::HPobject01::eHPState::Empty:
			empty();
			break;
		case ya::HPobject01::eHPState::Idle:
			idle();
			break;
		case ya::HPobject01::eHPState::Break:
			breakHp();
			break;
		case ya::HPobject01::eHPState::Refiil:
			reFill();
			break;
		default:
			break;
		}
	}

	void HPobject01::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HPobject01::Release()
	{
		GameObject::Release();
	}

	void HPobject01::empty()
	{
		if (emptyFlag == false)
		{
			emptyFlag = true;
			mAnimator->Play(L"Health001.Health Empty", false);
		}
	}
	void HPobject01::idle()
	{
		if (idleFlag == false)
		{
			idleFlag = true;
			mAnimator->Play(L"Health002.Health Idle", true);
		}
	}
	void HPobject01::breakHp()
	{
		if (breakHpFlag == false)
		{
			breakHpFlag = true;
			idleFlag = false;
			mAnimator->Play(L"Health003.Health Break", false);
		}
	}
	void HPobject01::reFill()
	{
		if (reFillFlag == false)
		{
			reFillFlag = true;
			emptyFlag = false;
			mAnimator->Play(L"Health004.Health Refill", false);
		}
	}

	void HPobject01::breakHPCompleteEvent()
	{
		mHPstate = eHPState::Empty;
		breakHpFlag = false;
	}

	void HPobject01::reFillCompleteEvent()
	{
		mHPstate = eHPState::Idle;
		reFillFlag = false;
	}
}

