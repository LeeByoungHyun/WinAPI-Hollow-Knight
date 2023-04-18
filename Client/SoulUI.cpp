#include "SoulUI.h"
#include "yaSceneManager.h"
#include "yaResourceManager.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaAnimation.h"

#include "yaPlayer.h"
#include "HPobject01.h"
#include "HPobject02.h"
#include "HPobject03.h"
#include "HPobject04.h"
#include "HPobject05.h"

namespace ya
{
	// 싱글톤 객체 초기화
	SoulUI* SoulUI::instance = nullptr;

	SoulUI::SoulUI()
	{

	}

	SoulUI::~SoulUI()
	{

	}

	void SoulUI::Initialize()
	{
		GameObject::Initialize();

		mPlayer = Player::GetInstance();

		mImage = ResourceManager::Load<Image>(L"SoulUI", L"..\\Resources\\UI\\Soul\\019.Soul Orb Glow\\019-00-127.bmp");
		temp = ResourceManager::Load<Image>(L"temp", L"..\\Resources\\UI\\Soul\\019.Soul Orb Glow\\temp.bmp");

		tr = AddComponent<Transform>();
		tr->SetPos(Vector2(51.0f, 67.0f));
		tr->SetSize(Vector2(0.7f, 0.7f));
	}

	void SoulUI::Update()
	{
		GameObject::Update();

		if (soul >= 100.0f)
			soul = 100.0f;
		if (soul <= 0.0f)
			soul = 0.0f;

		float remain = 100 - soul;
		//float mImageHeight = (mImage->GetHeight() / 100) * soul;
		float mImagePos = (mImage->GetHeight() / 100.0f) * remain;

		Vector2 pos = tr->GetPos();
		pos.y = 67 + mImagePos * 0.7f;
		tr->SetPos(pos);

		HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN oldPen = (HPEN)::SelectObject(temp->GetHdc(), hpen);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(temp->GetHdc(), hBrush);

		Rectangle(temp->GetHdc(), 0, 0, 129, 126);
		::DeleteObject(hpen);
		DeleteObject(hBrush);

		BitBlt(temp->GetHdc()
			, 0, 0	// soul이 줄어들수록 증가해야 함
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc()	
			, 0, mImagePos	// soul이 줄어들수록 감소해야 함
			, SRCCOPY);		

		//
	}

	void SoulUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Vector2 pos = tr->GetPos();
		TransparentBlt(hdc
			, pos.x, pos.y								
			, temp->GetWidth() * 0.7, temp->GetHeight() * 0.7	
			, temp->GetHdc()							
			, 0, 0										
			, temp->GetWidth(), temp->GetHeight()	
			, RGB(255, 0, 255));
	}

	void SoulUI::Release()
	{
		GameObject::Release();
	}
}

