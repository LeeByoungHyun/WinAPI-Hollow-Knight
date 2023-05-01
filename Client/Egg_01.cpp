#include "Egg_01.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaRigidBody.h"
#include "yaCamera.h"
#include "yaCollider.h"

#include "yaPlayer.h"

namespace ya
{
	Egg_01::Egg_01()
	{

	}

	Egg_01::~Egg_01()
	{

	}

	void Egg_01::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Egg_01", L"..\\Resources\\GodHome\\GG_gold_egg.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void Egg_01::Update()
	{
		GameObject::Update();
	}

	void Egg_01::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// 카메라 위치에 맞추어 좌표 계산
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);
		pos.x -= mImage->GetWidth() / 2;
		pos.y -= mImage->GetHeight();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * 0.7f, mImage->GetHeight() * 0.7f
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}

	void Egg_01::Release()
	{
		GameObject::Release();

	}
}