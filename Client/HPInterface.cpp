#include "HPInterface.h"
#include "yaSceneManager.h"
#include "yaResourceManager.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaImage.h"

#include "yaPlayer.h"
#include "HPobject01.h"
#include "HPobject02.h"
#include "HPobject03.h"
#include "HPobject04.h"
#include "HPobject05.h"

namespace ya
{
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
		hp01 = object::Instantiate<HPobject01>(Vector2(100.0f, 100.0f), eLayerType::UI);
		hp02 = object::Instantiate<HPobject02>(Vector2(150.0f, 100.0f), eLayerType::UI);
		hp03 = object::Instantiate<HPobject03>(Vector2(200.0f, 100.0f), eLayerType::UI);
		hp04 = object::Instantiate<HPobject04>(Vector2(250.0f, 100.0f), eLayerType::UI);
		hp05 = object::Instantiate<HPobject05>(Vector2(300.0f, 100.0f), eLayerType::UI);

		tr = AddComponent<Transform>();
		tr->SetPos(Vector2(50.0f, 50.0f));

		mImage = ResourceManager::Load<Image>(L"HUD", L"..\\Resources\\UI\\HUD\\018.HUD Frame\\018-05-118.bmp");

		mHPstate = eHPState::Remain05;
	}

	void HPInterface::Update()
	{
		GameObject::Update();

		activeScene = SceneManager::GetActiveScene();

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

		Vector2 pos = tr->GetPos();
		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}

	void HPInterface::Release()
	{
		GameObject::Release();
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
			mHPstate = eHPState::Remain04;
	}
}

