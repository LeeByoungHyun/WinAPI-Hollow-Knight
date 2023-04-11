#pragma once
#include "yaGameObject.h"

namespace ya
{
	class SphereBall : public GameObject
	{
	public:
		enum class eSphereBallState
		{
			Disable,
			Active,
			Ball
		};

		SphereBall();
		~SphereBall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetShereBallState(eSphereBallState state) { mState = state; }
		eSphereBallState GetShereBallState() { return mState; }
		bool GetActiveFlag() { return activeFlag; }

	private:
		void disable();
		void active();
		void ball();

		void ballCompleteEvent();

	private:
		class Animator* mAnimator;
		class Transform* tr;
		class Collider* mCollider;

		eSphereBallState mState;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;
		bool ballFlag = false;
	};
}
