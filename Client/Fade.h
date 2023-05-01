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

		enum class eColor
		{
			White,
			Black
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
		void SetFadeSpeed(int speed) { FadeSpeed = speed; }
		void SetFadeColor(eColor color);
		eFadeState GetFadeState() { return mState; }
		void SetAlpha(int num) { alpha = num; }
		int GetAlpha() { return alpha; }

	private:
		Image* mWhite;
		Image* mBlack;
		Image* mImage;
		Transform* tr;
		class Animator* mAnimator;
		HDC* mHdc;
		eFadeState mState;
		eColor mColor;

		int alpha;
		int FadeSpeed = 255;
		void neutral();
		void fadeIn();
		void fadeOut();

		bool neutralFlag;

		static Fade* instance;
	};
}


