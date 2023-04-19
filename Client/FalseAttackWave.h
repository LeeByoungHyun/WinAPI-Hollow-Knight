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

		void SetWaveState(eFalseAttackWaveState state) { mState = state; }
		eFalseAttackWaveState GetWaveState() { return mState; }
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
		class Wave01* wave02;
		class Wave02* wave03;
		class Wave02* wave04;
		class Wave02* wave05;
		class Wave03* wave06;
		class Wave03* wave07;
		class Wave03* wave08;
		class Wave02* wave09;
		class Wave02* wave10;
		class Wave01* wave11;

		float mTime = 0.0f;
		bool disableFlag = false;
		bool activeFlag = false;

		bool wave01Flag = false;
		bool wave02Flag = false;
		bool wave03Flag = false;
		bool wave04Flag = false;
		bool wave05Flag = false;
		bool wave06Flag = false;
		bool wave07Flag = false;
		bool wave08Flag = false;
		bool wave09Flag = false;
		bool wave10Flag = false;
		bool wave11Flag = false;
	};
}
