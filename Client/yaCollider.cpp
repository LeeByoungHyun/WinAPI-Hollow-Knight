#include "yaCollider.h"
#include "yaCollider.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaCamera.h"

namespace ya
{
	UINT Collider::ColliderNumber = 0;
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mCenter(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(100.0f, 100.0f)
		, mID(ColliderNumber++)
	{

	}

	Collider::~Collider()
	{

	}

	void Collider::Initialize()
	{

	}

	void Collider::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;
	}

	void Collider::Render(HDC hdc)
	{
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		Vector2 pos = Camera::CalculatePos(mPos);

		/*
		pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;
        pos.y -= mSpriteSheet[mSpriteIndex].size.y;
		*/

		//Rectangle(hdc, mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y);
		Rectangle(hdc, mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y);

		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);
	}

	void Collider::Release()
	{

	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
	}
}
