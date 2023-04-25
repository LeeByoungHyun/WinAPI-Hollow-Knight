#include "Spike_Large.h"
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
#include "Fade.h"

namespace ya
{
	Spike_Large::Spike_Large()
	{

	}

	Spike_Large::~Spike_Large()
	{

	}

	void Spike_Large::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Spike_Large", L"..\\Resources\\GodHome\\Spike_Large.bmp");
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(Vector2(5449.0f, 110.0f));
		mCollider->SetCenter(Vector2(-2725.0f, -110.0f));
		GameObject::Initialize();
	}

	void Spike_Large::Update()
	{
		GameObject::Update();

		if (testFlag == true)
		{
			mTime += Time::DeltaTime();

			if (mTime >= 3.0f)
			{
				Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeIn);
				Player::GetInstance()->SetPlayerState(Player::ePlayerState::WakeUp);
				Player::GetInstance()->GetComponent<Transform>()->SetPos(Vector2(500.0f, 2100.0f));
				Player::GetInstance()->GetComponent<RigidBody>()->SetGround(true);
				Player::GetInstance()->GetComponent<RigidBody>()->SetVelocity(Vector2::Zero);
				testFlag = false;
				mTime = 0.0f;
			}
		}
	}

	void Spike_Large::Render(HDC hdc)
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

	void Spike_Large::Release()
	{
		GameObject::Release();

	}

	void Spike_Large::OnCollisionEnter(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = Player::GetInstance();
			if (mplayer == nullptr)
				return;

			testFlag = true;
			//mplayer->SetPlayerState(Player::ePlayerState::Recoil);
		}
	}

	void Spike_Large::OnCollisionStay(Collider* other)
	{

	}

	void Spike_Large::OnCollisionExit(Collider* other)
	{

	}
}