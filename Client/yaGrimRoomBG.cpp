#include "yaGrimRoomBG.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"

namespace ya
{
	GrimRoomBG::GrimRoomBG()
	{

	}

	GrimRoomBG::~GrimRoomBG()
	{

	}

	void GrimRoomBG::Initialize()
	{
		//mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\room1.bmp");
		tr = AddComponent<Transform>();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\GrimBG\\test", Vector2::Zero, 1.0f);

		mAnimator->Play(L"GrimBGtest", false);

		GameObject::Initialize();
	}

	void GrimRoomBG::Update()
	{
		GameObject::Update();
	}

	void GrimRoomBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//BitBlt(hdc, tr->GetPos().x, tr->GetPos().y - 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void GrimRoomBG::Release()
	{
		GameObject::Release();

	}
}