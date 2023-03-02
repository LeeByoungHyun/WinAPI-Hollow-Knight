#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
#include "yaTransform.h"
#include "yaAnimator.h"

namespace ya
{
	// class Animator;
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			Idle,
			Move,
			Slash,
			Death,
		};

		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		ePlayerState mState;
		Image* mImage;
		Transform* tr;
		Animator* mAnimator;
	};
}



