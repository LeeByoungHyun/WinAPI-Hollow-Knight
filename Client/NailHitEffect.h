#pragma once
#include "yaGameObject.h"

namespace ya
{
	class NailHitEffect : public GameObject
	{
	public:
		NailHitEffect();
		~NailHitEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void nailHitEffectComplateEvent();

	private:
		class Animator* mAnimator;
		class Transform* tr;

		bool playFlag = false;
	};
}
