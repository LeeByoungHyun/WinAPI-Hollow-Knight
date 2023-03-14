#include "MantisLords.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"

namespace ya
{
	MantisLords::MantisLords()
	{

	}
	MantisLords::~MantisLords()
	{

	}
	void MantisLords::Initialize()
	{
		Transform* tr = GetComponent<Transform>();

		hp = 100;

		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Arrive\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Arrive\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Leave\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash Leave\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dash(Recover)\\right", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Death\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Death Leave\\neutral", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Arrive\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Land\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Dstab Leave\\neutral", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Bow\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Idle\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Leave\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Stand\\neutral", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throne Wounded\\neutral", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throw\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Throw\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Arrive\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Arrive\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 1)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 1)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 2)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Leave(Part 2)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Ready\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Mantis Lords\\Mantis Lords_Wall Ready\\right", Vector2::Zero, 0.1f);
	}
	void MantisLords::Update()
	{

	}
	void MantisLords::Render(HDC hdc)
	{

	}
	void MantisLords::Release()
	{

	}
	void MantisLords::OnCollisionEnter(Collider* other)
	{

	}
	void MantisLords::OnCollisionStay(Collider* other)
	{

	}
	void MantisLords::OnCollisionExit(Collider* other)
	{

	}

	void MantisLords::throneIdle()
	{
	}

	void MantisLords::throneBow()
	{
	}

	void MantisLords::throneStand()
	{
	}

	void MantisLords::throneLeave()
	{
	}

	void MantisLords::throneWounded()
	{
	}

	void MantisLords::dashArrive()
	{
	}

	void MantisLords::dashAnticipate()
	{
	}

	void MantisLords::dash()
	{
	}

	void MantisLords::dashRecover()
	{
	}

	void MantisLords::dashLeave()
	{
	}

	void MantisLords::wallArrive()
	{
	}

	void MantisLords::wallReady()
	{
	}

	void MantisLords::wallThrow()
	{
	}

	void MantisLords::wallLeave1()
	{
	}

	void MantisLords::wallLeave2()
	{
	}

	void MantisLords::death()
	{
	}

	void MantisLords::deathLeave()
	{
	}
	

}