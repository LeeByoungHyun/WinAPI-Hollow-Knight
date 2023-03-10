#include "yaCamera.h"
#include "yaApplication.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaTime.h"

extern ya::Application application;

const float CameraSpeed = 100.0f;

namespace ya
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
	}

	void Camera::Update()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mLookPosition.x -= CameraSpeed * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::RIGHT))
			mLookPosition.x += CameraSpeed * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::UP))
			mLookPosition.y -= CameraSpeed * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::DOWN))
			mLookPosition.y -= CameraSpeed * Time::DeltaTime();

		if (mTarget != nullptr)
		{
			mLookPosition
				= mTarget->GetComponent<Transform>()->GetPos();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}
}
