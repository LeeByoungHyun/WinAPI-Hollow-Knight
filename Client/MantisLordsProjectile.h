#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MantisLordsProjectile : public GameObject
	{
	public:
		enum class eProjectileState
		{
			Disable,
			Active
		};
		enum class eDirection
		{
			Left,
			Right
		};

		MantisLordsProjectile();
		~MantisLordsProjectile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetProjectileState(eProjectileState state) { mState = state; }
		eProjectileState GetProjectileState() { return mState; }
		void SetDirection(eDirection direct) { mDirection = direct; }
		eDirection GetDirection() { return mDirection; }
		void SetPos(Vector2 pos) { tr->SetPos(pos); }
		bool GetActiveFlag() { return activeFlag; }

	private:
		void disable();
		void active();

	private:
		class Animator* mAnimator;
		class Transform* tr;
		class Collider* mCollider;

		eProjectileState mState;
		eDirection mDirection;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;
	};
}
