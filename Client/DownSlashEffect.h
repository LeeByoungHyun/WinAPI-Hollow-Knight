#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class DownSlashEffect : public GameObject
	{
	public:
		DownSlashEffect();
		~DownSlashEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void downSlashEffectComplateEvent();

	private:
		Animator* mAnimator;
		class Transform* tr;
		class Player* player;
	};
}

