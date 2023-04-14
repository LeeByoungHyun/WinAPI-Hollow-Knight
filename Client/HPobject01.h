#pragma once
#include "yaGameObject.h"

namespace ya
{
	class HPobject01 : public GameObject
	{
	public:
		enum class eHPState
		{
			Empty,
			Idle,
			Break,
			Refiil
		};

		HPobject01();
		~HPobject01();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetState(eHPState state) { mHPstate = state; }

	private:
		void empty();
		void idle();
		void breakHp();
		void reFill();

		void breakHPCompleteEvent();
		void reFillCompleteEvent();

		class Animator* mAnimator;
		class Transform* tr;

		eHPState mHPstate;
		class Scene* activeScene;
		float mTime = 0.0f;

		bool emptyFlag = false;
		bool idleFlag = false;
		bool breakHpFlag = false;
		bool reFillFlag = false;
	};
}


