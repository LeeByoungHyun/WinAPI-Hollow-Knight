#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Cloud02 : public GameObject
	{
	public:

		Cloud02();
		~Cloud02();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


