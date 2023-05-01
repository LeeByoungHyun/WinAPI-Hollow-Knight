#include "Menu_Pointer_R.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"
#include "NailHitEffect.h"

namespace ya
{
	Menu_Pointer_R::Menu_Pointer_R()
	{

	}

	Menu_Pointer_R::~Menu_Pointer_R()
	{

	}

	void Menu_Pointer_R::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		Collider* mCollider = AddComponent<Collider>();
		tr = AddComponent<Transform>();
		tr->SetSize(Vector2(0.8f, 0.8f));

		mAnimator->CreateAnimations(L"..\\Resources\\Main_Menu\\pointer\\OFF\\right", Vector2::Zero, 0.016f);
		mAnimator->CreateAnimations(L"..\\Resources\\Main_Menu\\pointer\\ON\\right", Vector2::Zero, 0.016f);

		ePointerState = ePointerState::OffUI;

		GameObject::Initialize();
	}

	void Menu_Pointer_R::Update()
	{
		GameObject::Update();

		switch (ePointerState)
		{
		case ya::Menu_Pointer_R::ePointerState::OnUI:
			onUI();
			break;
		case ya::Menu_Pointer_R::ePointerState::OffUI:
			offUI();
			break;
		default:
			break;
		}
	}

	void Menu_Pointer_R::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Menu_Pointer_R::Release()
	{
		GameObject::Release();
	}

	void Menu_Pointer_R::OnCollisionEnter(Collider* other)
	{

	}

	void Menu_Pointer_R::OnCollisionStay(Collider* other)
	{
		
	}

	void Menu_Pointer_R::OnCollisionExit(Collider* other)
	{

	}
	void Menu_Pointer_R::onUI()
	{
		if (onFlag == false)
		{
			mAnimator->Play(L"ONright", false);
			onFlag = true;
			offFlag = false;
		}
		
	}
	void Menu_Pointer_R::offUI()
	{
		if (offFlag == false)
		{
			mAnimator->Play(L"OFFright", false);
			onFlag = false;
			offFlag = true;
		}
	}
}
