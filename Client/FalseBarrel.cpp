#include "FalseBarrel.h"
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

namespace ya
{
	FalseBarrel::FalseBarrel()
	{
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();
		tr = AddComponent<Transform>();
	}

	FalseBarrel::~FalseBarrel()
	{
		
	}

	void FalseBarrel::Initialize()
	{
		mAnimator->CreateAnimations(L"..\\Resources\\False Knight\\False Knight_Barrel(Fall)\\neutral", Vector2::Zero, 0.1f);

		mCollider->SetCenter(Vector2(-70.0f, -140.0f));
		mCollider->SetSize(Vector2(140.0f, 140.0f));

		mAnimator->Play(L"False Knight_Barrel(Fall)neutral", true);

		GameObject::Initialize();
	}

	void FalseBarrel::Update()
	{
		Vector2 pos = tr->GetPos();
		pos.y += 400.0f * Time::DeltaTime();
		tr->SetPos(pos);

		GameObject::Update();
	}

	void FalseBarrel::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseBarrel::Release()
	{
		GameObject::Release();
	}

	void FalseBarrel::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Ground)
		{
			// 파괴되는 이펙트 추가해야 함
			object::Destroy(this);
		}

		GameObject::OnCollisionEnter(other);
	}

	void FalseBarrel::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void FalseBarrel::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}
}