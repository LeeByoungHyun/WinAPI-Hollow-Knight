#pragma once
#include "yaGameObject.h"

namespace ya
{
	class WhiteTree01 : public GameObject
	{
	public:

		WhiteTree01();
		~WhiteTree01();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


