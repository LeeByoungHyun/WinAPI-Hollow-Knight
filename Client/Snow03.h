#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Snow03 : public GameObject
	{
	public:

		Snow03();
		~Snow03();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


