#include "yaCrawlid.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaScene.h"
#include "yaObject.h"

namespace ya
{
	Crawlid::Crawlid()
	{
	}
	Crawlid::~Crawlid()
	{
	}
	void Crawlid::Initialize()
	{
		hp = 3;

		Transform* tr = GetComponent<Transform>();
		//tr->SetSize(Vector2(0.5f, 0.5f));
		//tr->SetPos(Vector2(700.0f, 400.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Crawlid\\walk", Vector2::Zero, 0.1f);

		mAnimator->Play(L"Crawlidwalk", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetName(L"CrawlidCollider");
		mCollider->SetCenter(Vector2(-60.0f, -60.0f));
		mCollider->SetSize(Vector2(120.0f, 60.0f));

		GameObject::Initialize();
	}
	void Crawlid::Update()
	{
		GameObject::Update();

		if (hp <= 0)
		{
			object::Destroy(this);
		}
	}
	void Crawlid::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Crawlid::Release()
	{
		GameObject::Release();
	}
	void Crawlid::OnCollisionEnter(Collider* other)
	{
		// 플레이어에게 공격당하면 체력감소
		if (other->GetOwner()->GetType() == eLayerType::Effect)
		{
			hp -= 1;
		}
		
	}
	void Crawlid::OnCollisionStay(Collider* other)
	{
	}
	void Crawlid::OnCollisionExit(Collider* other)
	{
	}
}
