#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Wave03 : public GameObject
	{
	public:
		enum class eWave03State
		{
			Disable,
			Active,
		};

		Wave03();
		~Wave03();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetWaveState(eWave03State state) { mState = state; }
		eWave03State GetWaveState() { return mState; }
		bool GetActiveFlag() { return activeFlag; }
		void SetPos(Vector2 pos) { mPos = pos; }

	private:
		void disable();
		void active();

	private:
		class Transform* tr;
		class Collider* mCollider;
		class RigidBody* mRigidbody;
		eDirection mDirection;
		eWave03State mState;
		class Image* mImageL;
		class Image* mImageR;

		Vector2 mPos;
		Vector2 speed = Vector2::Zero;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;
	};
}
