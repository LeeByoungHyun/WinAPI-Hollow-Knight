#pragma once
#include "yaGameObject.h"

namespace ya
{
	class CounterAttackCollider : public GameObject
	{
	public:
		enum class eCounterAttackColliderState
		{
			Disable,
			Active,
		};

		CounterAttackCollider();
		~CounterAttackCollider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetCAState(eCounterAttackColliderState state) { mState = state; }
		eCounterAttackColliderState GetCAState() { return mState; }
		bool GetActiveFlag() { return activeFlag; }

	private:
		void disable();
		void active();

	private:
		class Transform* tr;
		class Collider* mCollider;
		eDirection mDirection;
		eCounterAttackColliderState mState;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;
	};
}
