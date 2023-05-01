#include "Mantis_Cage_T.h"
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
	Mantis_Cage_T::Mantis_Cage_T()
	{

	}

	Mantis_Cage_T::~Mantis_Cage_T()
	{

	}

	void Mantis_Cage_T::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Mantis_Cage_T", L"..\\Resources\\GodHome\\gg_4_cage_0005_3.bmp");
		tr = AddComponent<Transform>();

		tr->SetSize(Vector2(1.5f, 1.5f));

		GameObject::Initialize();
	}

	void Mantis_Cage_T::Update()
	{
		GameObject::Update();
	}

	void Mantis_Cage_T::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// 카메라 위치에 맞추어 좌표 계산
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);
		pos.x -= mImage->GetWidth() / 2;
		pos.y -= mImage->GetHeight();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}

	void Mantis_Cage_T::Release()
	{
		GameObject::Release();

	}
}