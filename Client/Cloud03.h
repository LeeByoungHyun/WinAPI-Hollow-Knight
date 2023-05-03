#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Cloud03 : public GameObject
	{
	public:

		Cloud03();
		~Cloud03();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


