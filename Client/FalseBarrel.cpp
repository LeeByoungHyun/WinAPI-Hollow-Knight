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
#include "ExplodeBarrelEffect.h"
#include "yaSound.h"

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

		explodeSound01 = ResourceManager::Load<Sound>(L"explodeSound01", L"..\\Resources\\Sound\\barrel_death_1.wav");
		explodeSound02 = ResourceManager::Load<Sound>(L"explodeSound02", L"..\\Resources\\Sound\\barrel_death_2.wav");
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
		if (otherType == eLayerType::Platform)
		{
			// 파괴되는 이펙트 추가해야 함
			object::Instantiate<ExplodeBarrelEffect>(tr->GetPos(), eLayerType::Effect);
			//srand((unsigned int)time(NULL));
			int sound = rand() % 2;
			if (sound == 0)
				explodeSound01->Play(false);
			else
				explodeSound02->Play(false);

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