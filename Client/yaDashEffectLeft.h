#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class DashEffectLeft : public GameObject
	{
	public:
		DashEffectLeft();
		~DashEffectLeft();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void dashEffectLeftComplateEvent();

	private:
		Animator* mAnimator;
		class Player* player;
	};
}
