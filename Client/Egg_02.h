#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Egg_02 : public GameObject
	{
	public:

		Egg_02();
		~Egg_02();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


