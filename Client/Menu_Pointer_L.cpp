#include "Menu_Pointer_L.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaPlayer.h"
#include "NailHitEffect.h"

namespace ya
{
	Menu_Pointer_L::Menu_Pointer_L()
	{

	}

	Menu_Pointer_L::~Menu_Pointer_L()
	{

	}

	void Menu_Pointer_L::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		player = Player::GetInstance();
		Collider* mCollider = AddComponent<Collider>();
		tr = AddComponent<Transform>();
		tr->SetSize(Vector2(0.8f, 0.8f));

		mAnimator->CreateAnimations(L"..\\Resources\\Main_Menu\\pointer\\OFF\\left", Vector2::Zero, 0.016f);
		mAnimator->CreateAnimations(L"..\\Resources\\Main_Menu\\pointer\\ON\\left", Vector2::Zero, 0.016f);

		ePointerState = ePointerState::OffUI;

		GameObject::Initialize();
	}

	void Menu_Pointer_L::Update()
	{
		GameObject::Update();

		switch (ePointerState)
		{
		case ya::Menu_Pointer_L::ePointerState::OnUI:
			onUI();
			break;
		case ya::Menu_Pointer_L::ePointerState::OffUI:
			offUI();
			break;
		default:
			break;
		}
	}

	void Menu_Pointer_L::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Menu_Pointer_L::Release()
	{
		GameObject::Release();
	}

	void Menu_Pointer_L::OnCollisionEnter(Collider* other)
	{

	}

	void Menu_Pointer_L::OnCollisionStay(Collider* other)
	{
		
	}

	void Menu_Pointer_L::OnCollisionExit(Collider* other)
	{

	}
	void Menu_Pointer_L::onUI()
	{
		if (onFlag == false)
		{
			mAnimator->Play(L"ONleft", false);
			onFlag = true;
			offFlag = false;
		}
		
	}
	void Menu_Pointer_L::offUI()
	{
		if (offFlag == false)
		{
			mAnimator->Play(L"OFFleft", false);
			onFlag = false;
			offFlag = true;
		}
	}
}
