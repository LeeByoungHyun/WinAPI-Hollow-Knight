#include "FalseKnight.h"
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
	FalseKnight::FalseKnight()
	{

	}

	FalseKnight::~FalseKnight()
	{

	}

	void FalseKnight::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Idle\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Run\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Land\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Land\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Anticipate)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Anticipate)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Recover)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Attack(Recover)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Up)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Up)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 1)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 1)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 2)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 2)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 3)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Jump Attack(Part 3)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll End)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Roll End)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Open)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Open)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Opened)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Opened)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Hit)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Stun(Hit)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Idle)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Idle)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Head(Hit)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 1)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 1)\\right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 2)\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Death(Head 2)\\right", Vector2::Zero, 0.1f);

		GameObject::Initialize();
	}

	void FalseKnight::Update()
	{
		GameObject::Update();
	}

	void FalseKnight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseKnight::Release()
	{
		GameObject::Release();
	}

	void FalseKnight::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void FalseKnight::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void FalseKnight::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}
}