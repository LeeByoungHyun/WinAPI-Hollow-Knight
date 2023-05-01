#include "MenuGameStart.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaCollider.h"
#include "Fade.h"
#include "yaSound.h"
#include "yaObject.h"
#include "Menu_Pointer_L.h"
#include "Menu_Pointer_R.h"

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

		pointerL = object::Instantiate<Menu_Pointer_L>(eLayerType::BGObject);
		pointerR = object::Instantiate<Menu_Pointer_R>(eLayerType::BGObject);

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
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Object)
		{
			pointerL->SetPointerState(Menu_Pointer_L::ePointerState::OnUI);
			pointerR->SetPointerState(Menu_Pointer_R::ePointerState::OnUI);

			pointerL->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, 75.0f));
			pointerR->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(225.0f, 75.0f));
		}

		GameObject::OnCollisionEnter(other);
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
		}

		GameObject::OnCollisionStay(other);
	}

	void MenuGameStart::OnCollisionExit(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Object)
		{
			pointerL->SetPointerState(Menu_Pointer_L::ePointerState::OffUI);
			pointerR->SetPointerState(Menu_Pointer_R::ePointerState::OffUI);
		}

		GameObject::OnCollisionEnter(other);
	}
}