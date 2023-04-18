#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FalseAttackCollider : public GameObject
	{
	public:
		enum class eFalseAttackColliderState
		{
			Disable,
			Active,
		};

		FalseAttackCollider();
		~FalseAttackCollider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetFAState(eFalseAttackColliderState state) { mState = state; }
		eFalseAttackColliderState GetFAState() { return mState; }
		bool GetActiveFlag() { return activeFlag; }

	private:
		void disable();
		void active();

	private:
		class Transform* tr;
		class Collider* mCollider;
		eDirection mDirection;
		eFalseAttackColliderState mState;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;
	};
}
