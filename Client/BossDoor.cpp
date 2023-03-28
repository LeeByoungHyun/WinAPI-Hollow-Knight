#include "BossDoor.h"
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
	BossDoor::BossDoor()
	{

	}

	BossDoor::~BossDoor()
	{

	}

	void BossDoor::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"BossDoor", L"..\\Resources\\GodHome\\BossDoor.bmp");
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(Vector2(300.0f, 200.0f));
		mCollider->SetCenter(Vector2(-150.0f, -200.0f));
		GameObject::Initialize();
	}

	void BossDoor::Update()
	{
		GameObject::Update();
	}

	void BossDoor::Render(HDC hdc)
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

	void BossDoor::Release()
	{
		GameObject::Release();

	}

	void BossDoor::OnCollisionEnter(Collider* other)
	{

	}

	void BossDoor::OnCollisionStay(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = Player::GetInstance();
			if (mplayer == nullptr)
				return;

			if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Down 
				&& mplayer->GetComponent<RigidBody>()->GetGround() == true)
			{
				mplayer->SetPlayerState(Player::ePlayerState::Enter);
			}

			if (mplayer->GetEnterComplateFlag() == true)
			{
				SceneManager::LoadScene(eSceneType::MantisLordsBoss);
			}
		}
	}

	void BossDoor::OnCollisionExit(Collider* other)
	{

	}
}