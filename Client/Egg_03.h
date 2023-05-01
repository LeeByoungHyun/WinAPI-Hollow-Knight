#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Egg_03 : public GameObject
	{
	public:

		Egg_03();
		~Egg_03();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


