#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Wave01 : public GameObject
	{
	public:
		enum class eWave01State
		{
			Disable,
			Active,
		};

		Wave01();
		~Wave01();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetWaveState(eWave01State state) { mState = state; }
		eWave01State GetWaveState() { return mState; }
		bool GetActiveFlag() { return activeFlag; }

	private:
		void disable();
		void active();

	private:
		class Transform* tr;
		class Collider* mCollider;
		class RigidBody* mRigidbody;
		eDirection mDirection;
		eWave01State mState;
		class Image* mImageL;
		class Image* mImageR;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;
	};
}
