#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Snow02 : public GameObject
	{
	public:

		Snow02();
		~Snow02();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


