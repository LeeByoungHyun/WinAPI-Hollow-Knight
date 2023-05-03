#include "MantisBossPlatform.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidBody.h"
#include "yaImage.h"
#include "yaCamera.h"

#include "yaPlayer.h"


namespace ya
{
	MantisBossPlatform::MantisBossPlatform()
	{

	}

	MantisBossPlatform::~MantisBossPlatform()
	{

	}

	void MantisBossPlatform::Initialize()
	{
		tr = AddComponent<Transform>();
		mImage = ResourceManager::Load<Image>(L"MantisBossPlatform", L"..\\Resources\\GodHome\\MantisBossPlatform.bmp");

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1182.0f, 99.0f));
		mCollider->SetCenter(Vector2(-591.0f, -99.0f));

		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		GameObject::Initialize();
	}

	void MantisBossPlatform::Update()
	{
		GameObject::Update();
	}

	void MantisBossPlatform::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// ī�޶� ��ġ�� ���߾� ��ǥ ���
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);
		pos.x -= mImage->GetWidth() / 2;
		pos.y -= mImage->GetHeight();

		TransparentBlt(hdc, pos.x, pos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));
	}

	void MantisBossPlatform::Release()
	{
		GameObject::Release();
	}

	void MantisBossPlatform::OnCollisionEnter(Collider* other)
	{
		
	}

	void MantisBossPlatform::OnCollisionStay(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();

			Vector2 dir = mplayer->GetComponent<RigidBody>()->GetVelocity().Normalize();	// �÷��̾� ���� ����

			Collider* playerCol = mplayer->GetComponent<Collider>();
			Vector2 playerColPos = playerCol->GetPos();
			Collider* objectCol = this->GetComponent<Collider>();
			Vector2 objectColPos = objectCol->GetPos();
			Transform* playerTr = mplayer->GetComponent<Transform>();
			Transform* objectTr = this->GetComponent<Transform>();
			Vector2 playerPos = playerTr->GetPos();
			Vector2 objectPos = objectTr->GetPos();

			// to right
			// �浹�� �÷��̾� y��ǥ�� ������Ʈ �ݶ��̴� ���̿� �ְ�,
			// �浹�� �÷��̾� x��ǥ�� ������Ʈ �ݶ��̴����� ���ʿ� �������� ����
			if ((0 < dir.x && dir.x <= 1)	// ���͹����� right�� ���
				&& playerPos.x < objectPos.x - objectCol->GetSize().x / 2
				&& playerPos.y - playerCol->GetSize().y < objectPos.y
				&& playerPos.y > objectPos.y - objectCol->GetSize().y)
			{
				playerPos.x = objectPos.x - objectCol->GetSize().x / 2 - playerCol->GetSize().x / 2 + 1.0f;
				playerTr->SetPos(playerPos);
				return;
			}
			// to left
			// �浹�� �÷��̾� y��ǥ�� ������Ʈ �ݶ��̴� ���̿� �ְ�,
			// �÷��̾� x��ǥ�� ������Ʈ �ݶ��̴����� �����ʿ� �������� ����
			if ((0 > dir.x && dir.x >= -1)	// ���͹����� left�� ���
				&& playerPos.x > objectPos.x + objectCol->GetSize().x / 2
				&& playerPos.y - playerCol->GetSize().y < objectPos.y
				&& playerPos.y > objectPos.y - objectCol->GetSize().y)
			{
				playerPos.x = objectPos.x + objectCol->GetSize().x / 2 + playerCol->GetSize().x / 2 - 1.0f;
				playerTr->SetPos(playerPos);
				return;
			}
			// to up
			// �浹�� �÷��̾� y��ǥ�� ������Ʈ �ݶ��̴����� �Ʒ��� �ְ�,
			// �÷��̾� x��ǥ�� ������Ʈ�ݶ��̴� ���̿� ��ġ�� ��� �Ʒ��� �о
			if ((0 > dir.y && dir.y >= -1)	// ���͹����� up�� ���
				&& playerPos.y - playerCol->GetSize().y < objectPos.y
				&& playerPos.y > objectPos.y
				&& playerPos.x > objectPos.x - objectCol->GetSize().x
				&& playerPos.x < objectPos.x + objectCol->GetSize().x)
			{
				playerPos.y = objectPos.y + playerCol->GetSize().y - 1.0f;
				playerTr->SetPos(playerPos);
				return;
			}
			// to down
			// �浹�� �÷��̾� y��ǥ�� ������Ʈ �ݶ��̴����� ���� �ְ�,
			// �÷��̾� x��ǥ�� ������Ʈ�ݶ��̴� ���̿� ��ġ�� ��쿡�� ����
			if ((0 < dir.y && dir.y <= 1)	// ���͹����� down�� ���
				&& playerPos.y > objectPos.y - objectCol->GetSize().y
				&& playerPos.y - playerCol->GetSize().y < objectPos.y - objectCol->GetSize().y
				&& playerPos.x > objectPos.x - objectCol->GetSize().x
				&& playerPos.x < objectPos.x + objectCol->GetSize().x)
			{
				playerPos.y = objectPos.y - objectCol->GetSize().y + 1;
				playerTr->SetPos(playerPos);
				rb->SetGround(true);
				if (mplayer->GetPlayerState() != Player::ePlayerState::Spike && (mplayer->GetPlayerState() != Player::ePlayerState::Skull)
					&& (mplayer->GetPlayerState() != Player::ePlayerState::Slash) && (mplayer->GetPlayerState() != Player::ePlayerState::SlashAlt)
					&& (mplayer->GetPlayerState() != Player::ePlayerState::UpSlash) && (mplayer->GetPlayerState() != Player::ePlayerState::DownSlash)
					&& (mplayer->GetPlayerState() != Player::ePlayerState::CastFireball) && (mplayer->GetPlayerState() != Player::ePlayerState::Dash)
					&& (mplayer->GetPlayerState() != Player::ePlayerState::WakeUp)) 
				{
					mplayer->SetPlayerState(Player::ePlayerState::Idle);
				}
				return;
			}
		}
	}

	void MantisBossPlatform::OnCollisionExit(Collider* other)
	{
		eLayerType otherType = other->GetOwner()->GetType();
		if (otherType == eLayerType::Player)
		{
			Player* mplayer = dynamic_cast<Player*>(other->GetOwner());
			if (mplayer == nullptr)
				return;

			RigidBody* rb = mplayer->GetComponent<RigidBody>();
			rb->SetGround(false);
		}
	}
}