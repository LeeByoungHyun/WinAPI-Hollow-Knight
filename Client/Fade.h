#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
#include "yaTransform.h"

namespace ya
{
	class Fade : public GameObject
	{
	public:
		enum class eFadeState
		{
			Neutral,
			FadeIn,
			FadeOut
		};

		Fade();
		~Fade();

		static Fade* GetInstance()
		{
			if (instance == nullptr)
				instance = new Fade();

			return instance;
		}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetFadeState(eFadeState state) { mState = state; }

	private:
		Image* mImage;
		Transform* tr;
		class Animator* mAnimator;
		HDC* mHdc;
		eFadeState mState;
		int alpha = 0;

		void neutral();
		void fadeIn();
		void fadeOut();

		static Fade* instance;
	};
}


