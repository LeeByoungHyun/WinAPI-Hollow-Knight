#pragma once
#include "yaGameObject.h"

namespace ya
{
	class WhiteTree02 : public GameObject
	{
	public:

		WhiteTree02();
		~WhiteTree02();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


