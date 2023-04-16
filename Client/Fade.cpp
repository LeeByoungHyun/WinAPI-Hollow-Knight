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
		mImage = ResourceManager::Load<Image>(L"fade", L"..\\Resources\\Fade.bmp");
		tr = AddComponent<Transform>();

		mState = eFadeState::Neutral;

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

		// 카메라 위치에 맞추어 좌표 계산
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		/*
		pos = Camera::CalculatePos(pos);
		pos.x -= mImage->GetWidth() / 2;
		pos.y -= mImage->GetHeight();
		*/
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
	void Fade::Release()
	{
		GameObject::Release();

	}

	void Fade::neutral()
	{

	}

	void Fade::fadeIn()
	{
		alpha -= 255 * Time::DeltaTime();
		if (alpha <= 0)
		{
			alpha = 0;
			mState = eFadeState::Neutral;
		}
	}

	void Fade::fadeOut()
	{
		alpha += 255 * Time::DeltaTime();
		if (alpha >= 255)
		{
			alpha = 255;
			mState = eFadeState::Neutral;
		}
	}
}