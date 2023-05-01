#include "Mantis_Cage_L.h"
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
	Mantis_Cage_L::Mantis_Cage_L()
	{

	}

	Mantis_Cage_L::~Mantis_Cage_L()
	{

	}

	void Mantis_Cage_L::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Mantis_Cage_L", L"..\\Resources\\GodHome\\mantis_Cage_L.bmp");
		tr = AddComponent<Transform>();

		GameObject::Initialize();
	}

	void Mantis_Cage_L::Update()
	{
		GameObject::Update();
	}

	void Mantis_Cage_L::Render(HDC hdc)
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

	void Mantis_Cage_L::Release()
	{
		GameObject::Release();

	}
}