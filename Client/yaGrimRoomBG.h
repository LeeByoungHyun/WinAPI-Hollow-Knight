#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
#include "yaTransform.h"

namespace ya
{
	class GrimRoomBG : public GameObject
	{
	public:

		GrimRoomBG();
		~GrimRoomBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage; 
		Transform* tr;
		class Animator* mAnimator;
	};
}


