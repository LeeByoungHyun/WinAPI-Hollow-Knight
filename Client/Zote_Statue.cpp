#include "Zote_Statue.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaRigidBody.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaSound.h"
#include "yaSoundManager.h"

#include "yaPlayer.h"
#include "Fade.h"

namespace ya
{
	Zote_Statue::Zote_Statue()
	{

	}

	Zote_Statue::~Zote_Statue()
	{

	}

	void Zote_Statue::Initialize()
	{
		mImage = ResourceManager::Load<Image>(L"Zote_Statue", L"..\\Resources\\GodHome\\Zote_Statue.bmp");
		tr = AddComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(Vector2(160.0f, 50.0f));
		mCollider->SetCenter(Vector2(-80.0f, -50.0f));

		victorySound = ResourceManager::Load<Sound>(L"VictorySound", L"..\\Resources\\Sound\\Hallownest_Call.wav");

		GameObject::Initialize();
	}

	void Zote_Statue::Update()
	{
		GameObject::Update();
	}

	void Zote_Statue::Render(HDC hdc)
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

	void Zote_Statue::Release()
	{
		GameObject::Release();

	}

	void Zote_Statue::OnCollisionEnter(Collider* other)
	{

	}

	void Zote_Statue::OnCollisionStay(Collider* other)
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
				mplayer->SetPlayerState(Player::ePlayerState::Challenge);
			}

			if (mplayer->GetChallengeComplateFlag() == true)
			{
				mTime += Time::DeltaTime();
				if (mTime >= 1.0f && flag1 == false)
				{
					Fade::GetInstance()->SetFadeColor(Fade::eColor::White);
					Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeOut);
					victorySound->Play(false);
					flag1 = true;
				}
				if (mTime >= 4.0f && flag2 == false)
				{
					//SceneManager::LoadScene(eSceneType::FalseKnightBoss);
					SceneManager::LoadScene(eSceneType::HornetBoss);
					mplayer->SetIdleFlag(false);
					mplayer->SetPlayerState(Player::ePlayerState::Idle);
					Fade::GetInstance()->SetFadeState(Fade::eFadeState::FadeIn);
					flag1 = false;
					flag2 = false;
					mTime = 0.0f;
				}
			}
		}
	}

	void Zote_Statue::OnCollisionExit(Collider* other)
	{

	}
	void Zote_Statue::InitializeFlag()
	{
		
	}
}