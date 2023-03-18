#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class FocusEffect : public GameObject
	{
	public:
		FocusEffect();
		~FocusEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void focusEffectComplateEvent();
		void focusEndEffectComplateEvent();

	private:
		Animator* mAnimator;
		class Player* player;

		bool endFlag = false;
	};
}
