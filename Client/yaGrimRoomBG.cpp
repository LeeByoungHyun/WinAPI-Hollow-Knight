#include "yaGrimRoomBG.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"


namespace ya
{
	GrimRoomBG::GrimRoomBG()
	{

	}

	GrimRoomBG::~GrimRoomBG()
	{

	}

	void GrimRoomBG::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"grimroom", L"..\\Resources\\room1.bmp");

		GameObject::Initialize();
	}

	void GrimRoomBG::Update()
	{
		GameObject::Update();
	}

	void GrimRoomBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, 0, -100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void GrimRoomBG::Release()
	{
		GameObject::Release();

	}
}