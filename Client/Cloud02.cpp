#include "Cloud02.h"
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
	Cloud02::Cloud02()
	{

	}

	Cloud02::~Cloud02()
	{

	}

	void Cloud02::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Cloud02", L"..\\Resources\\GodHome\\GG_scenery_0004_17_white.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void Cloud02::Update()
	{
		GameObject::Update();

		Vector2 pos = tr->GetPos();
		pos.x += 11.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (pos.x >= 5600.0f)
		{
			pos.x = 0.0f;
		}

	}

	void Cloud02::Render(HDC hdc)
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

	void Cloud02::Release()
	{
		GameObject::Release();

	}
}