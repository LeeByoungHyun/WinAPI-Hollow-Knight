#include "WhiteTree03.h"
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
	WhiteTree03::WhiteTree03()
	{

	}

	WhiteTree03::~WhiteTree03()
	{

	}

	void WhiteTree03::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"WhiteTree03", L"..\\Resources\\GodHome\\white_ash_scenery_0002_3.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void WhiteTree03::Update()
	{
		GameObject::Update();
	}

	void WhiteTree03::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// 카메라 위치에 맞추어 좌표 계산
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);
		pos.x -= mImage->GetWidth() / 2;
		pos.y -= mImage->GetHeight();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}

	void WhiteTree03::Release()
	{
		GameObject::Release();

	}
}