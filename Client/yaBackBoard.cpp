#include "yaBackboard.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"


namespace ya
{
	Backboard::Backboard()
	{

	}

	Backboard::~Backboard()
	{

	}

	void Backboard::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"backboard", L"..\\Resources\\backboard.bmp");

		GameObject::Initialize();
	}
	
	void Backboard::Update()
	{
		GameObject::Update();
	}

	void Backboard::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}

	void Backboard::Release()
	{
		GameObject::Release();

	}
}