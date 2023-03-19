#include "GodBG.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"

namespace ya
{
	GodBG::GodBG()
	{

	}

	GodBG::~GodBG()
	{

	}

	void GodBG::Initialize()
	{
		//mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\room1.bmp");
		tr = AddComponent<Transform>();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\GodHome\\BG", Vector2::Zero, 1.0f);

		mAnimator->Play(L"GodHomeBG", false);

		GameObject::Initialize();
	}

	void GodBG::Update()
	{
		GameObject::Update();
	}

	void GodBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//BitBlt(hdc, tr->GetPos().x, tr->GetPos().y - 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void GodBG::Release()
	{
		GameObject::Release();

	}
}