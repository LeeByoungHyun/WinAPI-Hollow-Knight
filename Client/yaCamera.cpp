#include "yaCamera.h"
#include "yaApplication.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaTime.h"

extern ya::Application application;

const float CameraSpeed = 200.0f;

namespace ya
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	float Camera::MinX = 0.0f;
	float Camera::MaxX = 0.0f;
	float Camera::MinY = 0.0f;
	float Camera::MaxY = 0.0f;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
	}

	void Camera::Update()
	{
		if (Input::GetKey(eKeyCode::NUM4))
			mLookPosition.x -= CameraSpeed * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::NUM6))
			mLookPosition.x += CameraSpeed * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::NUM8))
			mLookPosition.y -= CameraSpeed * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::NUM5))
			mLookPosition.y += CameraSpeed * Time::DeltaTime();

		if (mTarget != nullptr)
		{
			mLookPosition = mTarget->GetComponent<Transform>()->GetPos() + Vector2(0.0f, -300.0f);

			// 카메라 최대 이동거리를 넘어가면 조정
			if (mLookPosition.x <= MinX)
				mLookPosition.x = MinX;
			if (mLookPosition.x >= MaxX)
				mLookPosition.x = MaxX;
			if (mLookPosition.y >= MinY)
				mLookPosition.y = MinY;
			if (mLookPosition.y <= MaxY)
				mLookPosition.y = MaxY;
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}
}
