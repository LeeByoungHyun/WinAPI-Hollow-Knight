#include "Hornet.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaRigidBody.h"
#include "yaCamera.h"
#include "yaSound.h"

namespace ya
{
	// ΩÃ±€≈Ê ∞¥√º √ ±‚»≠
	Hornet* Hornet::instance = nullptr;

	Hornet::Hornet()
	{
		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		curScene = SceneManager::GetActiveScene();
		mRigidBody = AddComponent<RigidBody>();
		mCollider = AddComponent<Collider>();
	}

	Hornet::~Hornet()
	{

	}

	void Hornet::Initialize()
	{
		// æ÷¥œ∏ﬁ¿Ãº«
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Hornet\\Hornet_Idle\\right", Vector2::Zero, 0.1f);
	}

	void Hornet::Update()
	{

	}

	void Hornet::Render(HDC hdc)
	{

	}

	void Hornet::Release()
	{

	}

	void Hornet::OnCollisionEnter(Collider* other)
	{

	}

	void Hornet::OnCollisionStay(Collider* other)
	{

	}

	void Hornet::OnCollisionExit(Collider* other)
	{

	}
}
