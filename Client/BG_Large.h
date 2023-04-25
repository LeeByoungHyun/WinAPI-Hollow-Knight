#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
#include "yaTransform.h"

namespace ya
{
	class BG_Large : public GameObject
	{
	public:

		BG_Large();
		~BG_Large();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Transform* tr;
		class Animator* mAnimator;
		HDC* mHdc;
	};
}


