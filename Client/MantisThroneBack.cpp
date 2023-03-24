#include "MantisThroneBack.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaRigidBody.h"
#include "yaCamera.h"

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
		mImage = ResourceManager::Load<Image>(L"gg_mantis_throne_back", L"..\\Resources\\GodHome\\gg_mantis_throne_back.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void MantisThroneBack::Update()
	{
		GameObject::Update();
	}

	void MantisThroneBack::Render(HDC hdc)
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

	void MantisThroneBack::Release()
	{
		GameObject::Release();

	}
}