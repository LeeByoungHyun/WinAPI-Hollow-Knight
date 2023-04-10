#pragma once
#include "yaComponent.h"

namespace ya
{
	class RigidBody : public Component
	{
	public:
		RigidBody();
		~RigidBody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force);
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void SetGravity(Vector2 gravity) { mGravity = gravity; }
		Vector2 GetVelocity() { return mVelocity; }
		bool GetGround() { return mbGround; }
		void SetActive(bool state) { mActive = state; }

	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mFriction;
		bool mbGround;
		bool mActive = true;

		/*float mStaticFriction;
		float mKineticFriction;*/
		//float mCoefficientFriction;
		//float mNormalForce;
	};
}
