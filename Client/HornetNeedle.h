#pragma once
#include "yaGameObject.h"

namespace ya
{
	class HornetNeedle : public GameObject
	{
	public:
		enum class eHornetNeedleState
		{
			Disable,
			Active,
		};

		HornetNeedle();
		~HornetNeedle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetNeedeState(eHornetNeedleState state) { mState = state; }
		eHornetNeedleState GetNeedleState() { return mState; }
		bool GetActiveFlag() { return activeFlag; }
		void SetneedleDirection(eDirection dir) { mDirection = dir; }
		float GetNeedleSpeed() { return NEEDLESPEED; }

	private:
		void disable();
		void active();

	private:
		class Animator* mAnimator;
		class Transform* tr;
		class Collider* mCollider;
		eDirection mDirection;
		eHornetNeedleState mState;

		float NEEDLESPEED = 1500.0f;
		float DECELERATION = 1200.0f;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;
	};
}
