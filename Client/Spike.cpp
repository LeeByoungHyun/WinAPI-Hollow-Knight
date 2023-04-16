#include "Spike.h"
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
	Spike::Spike()
	{

	}

	Spike::~Spike()
	{

	}

	void Spike::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"spike", L"..\\Resources\\GodHome\\mantis_spikes.bmp");
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(Vector2(150.0f, 80.0f));
		mCollider->SetCenter(Vector2(-75.0f, -80.0f));
		GameObject::Initialize();
	}

	void Spike::Update()
	{
		GameObject::Update();
	}

	void Spike::Render(HDC hdc)
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

	void Spike::Release()
	{
		GameObject::Release();

	}

	void Spike::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = Player::GetInstance();
			if (mplayer == nullptr)
				return;

			//mplayer->SetPlayerState(Player::ePlayerState::Recoil);
		}
	}

	void Spike::OnCollisionStay(Collider* other)
	{
		
	}

	void Spike::OnCollisionExit(Collider* other)
	{

	}
}