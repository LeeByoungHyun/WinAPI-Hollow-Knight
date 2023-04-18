#include "Fade.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCamera.h"

namespace ya
{
	Fade* Fade::instance = nullptr;

	Fade::Fade()
	{

	}

	Fade::~Fade()
	{

	}

	void Fade::Initialize()
	{
		mWhite = ResourceManager::Load<Image>(L"fadeWhite", L"..\\Resources\\Fade.bmp");
		mBlack = ResourceManager::Load<Image>(L"fadeBlack", L"..\\Resources\\FadeBlack.bmp");
		mImage = mWhite;
		tr = AddComponent<Transform>();
		alpha = 0;

		mState = eFadeState::Neutral;
		mColor = eColor::White;

		GameObject::Initialize();
	}

	void Fade::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case eFadeState::Neutral:
			neutral();
			break;

		case eFadeState::FadeIn:
			fadeIn();
			break;

		case eFadeState::FadeOut:
			fadeOut();
			break;
		}
	}

	void Fade::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		if (neutralFlag == false)
		{
			// 카메라 위치에 맞추어 좌표 계산
			tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;    // 24비트 = 0, 32비트 = AC_SRC_ALPHA
			func.SourceConstantAlpha = alpha; // 0(투명) ~ 255(불투명) 알파값

			AlphaBlend(hdc, 0, 0
				, mImage->GetWidth()
				, mImage->GetHeight()
				, mImage->GetHdc()
				, 0, 0
				, mImage->GetWidth(), mImage->GetHeight()
				, func);
		}
	}
	void Fade::Release()
	{
		GameObject::Release();

	}

	void Fade::SetFadeColor(eColor color)
	{
		if (color == eColor::White)
			mImage = mWhite;
		else if (color == eColor::Black)
			mImage = mBlack;
	}

	void Fade::neutral()
	{
		if (neutralFlag == false)
		{
			neutralFlag = true;
		}
	}

	void Fade::fadeIn()
	{
		alpha -= FadeSpeed * Time::DeltaTime();
		neutralFlag = false;
		if (alpha <= 0)
		{
			alpha = 0;
			mState = eFadeState::Neutral;
		}
	}

	void Fade::fadeOut()
	{
		alpha += FadeSpeed * Time::DeltaTime();
		neutralFlag = false;
		if (alpha >= 255)
		{
			alpha = 255;
			//mState = eFadeState::Neutral;
		}
	}
}