#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class UpSlashEffect : public GameObject
	{
	public:
		UpSlashEffect();
		~UpSlashEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void upSlashEffectComplateEvent();

	private:
		Animator* mAnimator;
		class Transform* tr;
		class Player* player;
	};
}

