#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FalseAttackWave : public GameObject
	{
	public:
		enum class eFalseAttackWaveState
		{
			Disable,
			Active,
		};

		FalseAttackWave();
		~FalseAttackWave();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetFAState(eFalseAttackWaveState state) { mState = state; }
		eFalseAttackWaveState GetFAState() { return mState; }
		bool GetActiveFlag() { return activeFlag; }

	private:
		void disable();
		void active();

	private:
		class Transform* tr;
		class Collider* mCollider;
		eDirection mDirection;
		eFalseAttackWaveState mState;
		class Wave01* wave01;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;

		bool wave01Flag = false;
	};
}
