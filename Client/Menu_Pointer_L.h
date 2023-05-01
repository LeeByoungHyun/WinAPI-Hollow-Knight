#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Menu_Pointer_L : public GameObject
	{
	public:
		enum class ePointerState
		{
			OnUI,
			OffUI
		};

		Menu_Pointer_L();
		~Menu_Pointer_L();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPointerState(ePointerState state) { ePointerState = state; }

	private:
		void onUI();
		void offUI();

	private:
		Animator* mAnimator;
		GameObject* CollisionObj;
		class Player* player;
		class Transform* tr;
		ePointerState ePointerState;
		bool hitFlag = false;
		bool onFlag = false;
		bool offFlag = false;
	};
}

