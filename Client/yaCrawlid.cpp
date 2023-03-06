#include "yaCrawlid.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaScene.h"


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
	}
	void Crawlid::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Crawlid::Release()
	{
		GameObject::Release();
	}
}
