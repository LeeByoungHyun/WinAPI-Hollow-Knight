#include "HPobject05.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaTransform.h"

namespace ya
{
	HPobject05::HPobject05()
	{

	}

	HPobject05::~HPobject05()
	{

	}

	void HPobject05::Initialize()
	{
		GameObject::Initialize();

		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();

		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\001.Health Empty", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\002.Health Idle", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\003.Health Break", Vector2::Zero, 0.066f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Health\\004.Health Refill", Vector2::Zero, 0.066f);

		mAnimator->GetCompleteEvent(L"Health003.Health Break") = std::bind(&HPobject05::breakHPCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Health004.Health Refill") = std::bind(&HPobject05::reFillCompleteEvent, this);

		mAnimator->Play(L"Health002.Health Idle", true);
	}

	void HPobject05::Update()
	{
		GameObject::Update();

		activeScene = SceneManager::GetActiveScene();

		switch (mHPstate)
		{
		case ya::HPobject05::eHPState::Empty:
			empty();
			break;
		case ya::HPobject05::eHPState::Idle:
			idle();
			break;
		case ya::HPobject05::eHPState::Break:
			breakHp();
			break;
		case ya::HPobject05::eHPState::Refiil:
			reFill();
			break;
		default:
			break;
		}
	}

	void HPobject05::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HPobject05::Release()
	{
		GameObject::Release();
	}

	void HPobject05::empty()
	{
		if (emptyFlag == false)
		{
			emptyFlag = true;
			mAnimator->Play(L"Health001.Health Empty", false);
		}
	}
	void HPobject05::idle()
	{
		if (idleFlag == false)
		{
			idleFlag = true;
			mAnimator->Play(L"Health002.Health Idle", true);
		}
	}
	void HPobject05::breakHp()
	{
		if (breakHpFlag == false)
		{
			breakHpFlag = true;
			idleFlag = false;
			mAnimator->Play(L"Health003.Health Break", false);
		}
	}
	void HPobject05::reFill()
	{
		if (reFillFlag == false)
		{
			reFillFlag = true;
			emptyFlag = false;
			mAnimator->Play(L"Health004.Health Refill", false);
		}
	}

	void HPobject05::breakHPCompleteEvent()
	{
		mHPstate = eHPState::Empty;
		breakHpFlag = false;
	}

	void HPobject05::reFillCompleteEvent()
	{
		mHPstate = eHPState::Idle;
		reFillFlag = false;
	}
}

