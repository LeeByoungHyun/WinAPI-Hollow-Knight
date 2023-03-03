#include "yaSlashEffect.h"
#include "yaTransform.h"
#include "yaAnimator.h"

namespace ya
{
	SlashEffect::SlashEffect()
	{

	}

	SlashEffect::~SlashEffect()
	{

	}

	void SlashEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\007.SlashEffect", Vector2::Zero, 0.1f);
		mAnimator->SetName(L"SlashEffectAnimator");

		mAnimator->Play(L"Knight007.SlashEffect", false);

		GameObject::Initialize();
	}

	void SlashEffect::Update()
	{
		GameObject::Update();
	}

	void SlashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		
		
		/*
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 255));

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		Ellipse(hdc, pos.x, pos.y, pos.x + 50, pos.y + 50);

		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);
		*/
	}

	void SlashEffect::Release()
	{
		GameObject::Release();

	}
}
