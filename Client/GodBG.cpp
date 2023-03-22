#include "GodBG.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCamera.h"

namespace ya
{
	GodBG::GodBG()
	{

	}

	GodBG::~GodBG()
	{

	}

	void GodBG::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\GodHome\\GodBG.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void GodBG::Update()
	{
		GameObject::Update();
	}

	void GodBG::Render(HDC hdc)
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

	void GodBG::Release()
	{
		GameObject::Release();

	}
}