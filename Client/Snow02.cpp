#include "Snow02.h"
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
	Snow02::Snow02()
	{

	}

	Snow02::~Snow02()
	{

	}

	void Snow02::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Snow02", L"..\\Resources\\GodHome\\white_ash_scenery_0003_4.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void Snow02::Update()
	{
		GameObject::Update();
	}

	void Snow02::Render(HDC hdc)
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

	void Snow02::Release()
	{
		GameObject::Release();

	}
}