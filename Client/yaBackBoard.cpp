#include "yaBackBoard.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"


namespace ya
{
	BackBoard::BackBoard()
	{

	}

	BackBoard::~BackBoard()
	{

	}

	void BackBoard::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"backboard", L"..\\Resources\\backboard.bmp");

		GameObject::Initialize();
	}
	
	void BackBoard::Update()
	{
		GameObject::Update();
	}

	void BackBoard::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void BackBoard::Release()
	{
		GameObject::Release();

	}
}