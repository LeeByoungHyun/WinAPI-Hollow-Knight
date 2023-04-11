#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Barb04 : public GameObject
	{
	public:
		enum class eBarbState
		{
			Disable,
			Active,
			Thread,
			Spike,
			Loose,
			Break
		};

		Barb04();
		~Barb04();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetBarbState(eBarbState state) { mState = state; }
		eBarbState GetBarbState() { return mState; }
		//void SetPos(Vector2 pos) { tr->SetPos(pos); }
		bool GetActiveFlag() { return activeFlag; }

	private:
		void disable();
		void active();
		void thread();
		void spike();
		void loose();
		void barbBreak();

		void threadCompleteEvent();
		void looseCompleteEvent();
		void breakCompleteEvent();

	private:
		class Animator* mAnimator;
		class Transform* tr;
		class Collider* mCollider;

		eBarbState mState;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;

		bool threadFlag = false;
		bool spikeFlag = false;
		bool looseFlag = false;
		bool breakFlag = false;
		bool hitFlag = false;
	};
}
