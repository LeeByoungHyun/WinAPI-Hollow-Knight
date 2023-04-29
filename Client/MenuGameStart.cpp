#include "MenuGameStart.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaCollider.h"
#include "Fade.h"
#include "yaSound.h"

namespace ya
{
	MenuGameStart::MenuGameStart()
	{

	}

	MenuGameStart::~MenuGameStart()
	{

	}

	void MenuGameStart::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"menu_gameStart", L"..\\Resources\\TitleScene\\gameStart.bmp");
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();

		tr->SetPos(Vector2(700.0f, 500.0f));
		mCollider->SetSize(Vector2(160.0f, 40.0f));
		mCollider->SetCenter(Vector2(22.0f, 16.0f));

		buttonSound = ResourceManager::Load<Sound>(L"buttonSound", L"..\\Resources\\Sound\\ui_button_confirm.wav");

		GameObject::Initialize();
	}

	void MenuGameStart::Update()
	{
		GameObject::Update();

		if (flag == true)
		{
			mTime += Time::DeltaTime();
		}

		if (mTime >= 3.0f)
		{
			SceneManager::LoadScene(eSceneType::Tutorial);
			mTime = 0.0f;
			flag = false;
		}
	}

	void MenuGameStart::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		TransparentBlt(hdc, 700, 500, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}

	void MenuGameStart::Release()
	{
		GameObject::Release();
	}
	void MenuGameStart::OnCollisionEnter(Collider* other)
	{
	}
	void MenuGameStart::OnCollisionStay(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Object)
		{
			if (Input::GetKeyState(eKeyCode::LBUTTON) == eKeyState::Down)
			{
				Fade::GetInstance()->SetFadeColor(Fade::eColor::Black);
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeOut);
				buttonSound->Play(false);
				flag = true;
			}

			/*
			mTime += Time::DeltaTime();

			if (mTime >= 3.0f && flag == false)
			{
				Fade::GetInstance()->SetFadeColor(Fade::eColor::White);
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeOut);
				//victorySound->Play(false);
				flag = true;
			}
			if (mTime >= 8.0f && flag2 == false)
			{
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeIn);
				SceneManager::LoadScene(eSceneType::HornetBoss);
				mTime = 0.0f;
				flag2 = true;
			}
			*/
		}

		GameObject::OnCollisionStay(other);
	}
	void MenuGameStart::OnCollisionExit(Collider* other)
	{
	}
}