#include "MantisThrone.h"
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
	MantisThrone::MantisThrone()
	{

	}

	MantisThrone::~MantisThrone()
	{

	}

	void MantisThrone::Initialize()
	{
		//mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\room1.bmp");
		tr = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\GodHome\\Mantis Throne\\Throne", Vector2::Zero, 1.0f);

		mAnimator->Play(L"Mantis ThroneThrone", false);

		GameObject::Initialize();
	}

	void MantisThrone::Update()
	{
		GameObject::Update();
	}

	void MantisThrone::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//BitBlt(hdc, tr->GetPos().x, tr->GetPos().y - 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void MantisThrone::Release()
	{
		GameObject::Release();

	}
	void MantisThrone::OnCollisionEnter(Collider* other)
	{
		
	}
	void MantisThrone::OnCollisionStay(Collider* other)
	{

	}
	void MantisThrone::OnCollisionExit(Collider* other)
	{
		
	}
}