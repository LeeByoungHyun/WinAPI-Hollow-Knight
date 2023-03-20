#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class MantisThroneBack : public GameObject
	{
	public:

		MantisThroneBack();
		~MantisThroneBack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		Image* mImage;
		class Transform* tr;
		class Animator* mAnimator;
	};
}

