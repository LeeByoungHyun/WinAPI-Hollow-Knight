#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Cloud01 : public GameObject
	{
	public:

		Cloud01();
		~Cloud01();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


