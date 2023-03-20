#include "MantisThroneBack.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaRigidBody.h"

#include "yaPlayer.h"

namespace ya
{
	MantisThroneBack::MantisThroneBack()
	{

	}

	MantisThroneBack::~MantisThroneBack()
	{

	}

	void MantisThroneBack::Initialize()
	{
		//mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\room1.bmp");
		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\GodHome\\MantisThrone Back", Vector2::Zero, 1.0f);

		mAnimator->Play(L"GodHomeMantisThrone Back", false);

		GameObject::Initialize();
	}

	void MantisThroneBack::Update()
	{
		GameObject::Update();
	}

	void MantisThroneBack::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//BitBlt(hdc, tr->GetPos().x, tr->GetPos().y - 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void MantisThroneBack::Release()
	{
		GameObject::Release();

	}
	void MantisThroneBack::OnCollisionEnter(Collider* other)
	{

	}
	void MantisThroneBack::OnCollisionStay(Collider* other)
	{

	}
	void MantisThroneBack::OnCollisionExit(Collider* other)
	{

	}
}