#include "PlayerSkull.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"

namespace ya
{
	PlayerSkull::PlayerSkull()
	{

	}

	PlayerSkull::~PlayerSkull()
	{

	}

	void PlayerSkull::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\Knight\\Knight_DeathSkull\\Neutral\\020-00-112.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Knight\\Knight_DeathSkull\\Neutral", Vector2::Zero, 0.033f);

		mAnimator->Play(L"Knight_DeathSkullNeutral", true);

		GameObject::Initialize();
	}

	void PlayerSkull::Update()
	{
		GameObject::Update();
	}

	void PlayerSkull::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerSkull::Release()
	{
		GameObject::Release();
	}
}