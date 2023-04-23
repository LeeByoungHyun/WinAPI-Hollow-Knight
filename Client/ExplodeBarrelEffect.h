#pragma once
#include "yaGameObject.h"

namespace ya
{
	class ExplodeBarrelEffect : public GameObject
	{
	public:
		ExplodeBarrelEffect();
		~ExplodeBarrelEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void ExplodeBarrelEffectComplateEvent();

	private:
		class Animator* mAnimator;
		class Transform* tr;

		bool playFlag = false;
	};
}
