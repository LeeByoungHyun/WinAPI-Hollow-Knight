#include "HPInterface.h"
#include "yaSceneManager.h"
#include "yaResourceManager.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaInput.h"

#include "yaPlayer.h"
#include "HPobject01.h"
#include "HPobject02.h"
#include "HPobject03.h"
#include "HPobject04.h"
#include "HPobject05.h"

namespace ya
{
	// 싱글톤 객체 초기화
	HPInterface* HPInterface::instance = nullptr;

	HPInterface::HPInterface()
	{

	}

	HPInterface::~HPInterface()
	{

	}

	void HPInterface::Initialize()
	{
		GameObject::Initialize();

		mPlayer = Player::GetInstance();

		hp01 = HPobject01::GetInstance();
		hp02 = HPobject02::GetInstance();
		hp03 = HPobject03::GetInstance();
		hp04 = HPobject04::GetInstance();
		hp05 = HPobject05::GetInstance();

		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		tr->SetPos(Vector2(50.0f, 50.0f));
		tr->SetSize(Vector2(0.7f, 0.7f));

		mAnimator->CreateAnimations(L"..\\Resources\\UI\\HUD\\018.HUD Frame", Vector2::Zero, 0.066f);
		mAnimator->setUseCamera(false);

		mAnimator->Play(L"HUD018.HUD Frame", false);

		//mImage = ResourceManager::Load<Image>(L"HUD", L"..\\Resources\\UI\\HUD\\018.HUD Frame\\018-05-118.bmp");

		mHPstate = eHPState::Remain05;
	}

	void HPInterface::Update()
	{
		GameObject::Update();

		activeScene = SceneManager::GetActiveScene();

		// F 체력회복
		if (Input::GetKeyDown(eKeyCode::F))
		{
			initializeHP();
		}

		switch (mHPstate)
		{
		case ya::HPInterface::eHPState::Remain00:
			remain00();
			break;
		case ya::HPInterface::eHPState::Remain01:
			remain01();
			break;
		case ya::HPInterface::eHPState::Remain02:
			remain02();
			break;
		case ya::HPInterface::eHPState::Remain03:
			remain03();
			break;
		case ya::HPInterface::eHPState::Remain04:
			remain04();
			break;
		case ya::HPInterface::eHPState::Remain05:
			remain05();
			break;
		default:
			break;
		}
	}

	void HPInterface::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		/*
		Vector2 pos = tr->GetPos();
		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		*/
	}

	void HPInterface::Release()
	{
		GameObject::Release();
	}

	void HPInterface::initializeHP()
	{
		hp01->SetState(HPobject01::eHPState::Idle);
		hp02->SetState(HPobject02::eHPState::Idle);
		hp03->SetState(HPobject03::eHPState::Idle);
		hp04->SetState(HPobject04::eHPState::Idle);
		hp05->SetState(HPobject05::eHPState::Idle);
		hp01->initializeFlag();
		hp02->initializeFlag();
		hp03->initializeFlag();
		hp04->initializeFlag();
		hp05->initializeFlag();
		remainFlag00 = false;
		remainFlag01 = false;
		remainFlag02 = false;
		remainFlag03 = false;
		remainFlag04 = false;
		remainFlag05 = false;
		mHPstate = eHPState::Remain05;
		Player::GetInstance()->SetHP(5);
	}

	void HPInterface::remain00()
	{
		if (remainFlag00 == false)
		{
			remainFlag00 = true;

			if (remainFlag01 == true)	// hp 1에서 0으로 내려온 경우
			{
				hp01->SetState(HPobject01::eHPState::Break);
				remainFlag01 = false;
			}
		}
	}

	void HPInterface::remain01()
	{
		if (remainFlag01 == false)
		{
			remainFlag01 = true;

			if (remainFlag02 == true)	// hp 2에서 1로 내려온 경우
			{
				hp02->SetState(HPobject02::eHPState::Break);
				remainFlag02 = false;
			}
		}

		if (mPlayer->GetHp() == 0)
			mHPstate = eHPState::Remain00;
		else if (mPlayer->GetHp() == 2)
			mHPstate = eHPState::Remain02;
	}

	void HPInterface::remain02()
	{
		if (remainFlag02 == false)
		{
			remainFlag02 = true;

			if (remainFlag03 == true)	// hp 3에서 2로 내려온 경우
			{
				hp03->SetState(HPobject03::eHPState::Break);
				remainFlag03 = false;
			}
			else if (remainFlag01 == true)	// 1에서 2로 올라온 경우
			{
				hp02->SetState(HPobject02::eHPState::Refiil);
				remainFlag01 = false;
			}
		}

		if (mPlayer->GetHp() == 1)
			mHPstate = eHPState::Remain01;
		else if (mPlayer->GetHp() == 3)
			mHPstate = eHPState::Remain03;
	}

	void HPInterface::remain03()
	{
		if (remainFlag03 == false)
		{
			remainFlag03 = true;

			if (remainFlag04 == true)	// hp 4에서 3으로 내려온 경우
			{
				hp04->SetState(HPobject04::eHPState::Break);
				remainFlag04 = false;
			}
			else if (remainFlag02 == true)	// 2에서 3으로 올라온 경우
			{
				hp03->SetState(HPobject03::eHPState::Refiil);
				remainFlag02 = false;
			}
		}

		if (mPlayer->GetHp() == 2)
			mHPstate = eHPState::Remain02;
		else if (mPlayer->GetHp() == 4)
			mHPstate = eHPState::Remain04;
	}

	void HPInterface::remain04()
	{
		if (remainFlag04 == false)
		{
			remainFlag04 = true;

			if (remainFlag05 == true)	// hp 5에서 4로 내려온 경우
			{
				hp05->SetState(HPobject05::eHPState::Break); 
				remainFlag05 = false;
			}
			else if (remainFlag03 == true)	// 3에서 4로 올라온 경우
			{
				hp04->SetState(HPobject04::eHPState::Refiil);
				remainFlag03 = false;
			}
		}

		if (mPlayer->GetHp() == 3)
			mHPstate = eHPState::Remain03;
		else if (mPlayer->GetHp() == 5)
			mHPstate = eHPState::Remain05;
	}

	void HPInterface::remain05()
	{
		if (remainFlag05 == false)
		{
			remainFlag05 = true;

			if (remainFlag04 == true)	// 4에서 5로 올라온 경우
			{
				hp05->SetState(HPobject05::eHPState::Refiil);
				remainFlag04 = false;
			}
		}

		if (mPlayer->GetHp() == 4)	
		{
			mHPstate = eHPState::Remain04;
		}
	}
}

