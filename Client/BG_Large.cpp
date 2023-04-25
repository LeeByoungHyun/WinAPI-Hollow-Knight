#include "BG_Large.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCamera.h"

namespace ya
{
	BG_Large::BG_Large()
	{

	}

	BG_Large::~BG_Large()
	{

	}

	void BG_Large::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"BG_Large", L"..\\Resources\\GodHome\\BG_Large.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void BG_Large::Update()
	{
		GameObject::Update();
	}

	void BG_Large::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// 카메라 위치에 맞추어 좌표 계산
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);
		pos.x -= mImage->GetWidth() / 2;
		pos.y -= mImage->GetHeight();

		BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void BG_Large::Release()
	{
		GameObject::Release();
	}
}