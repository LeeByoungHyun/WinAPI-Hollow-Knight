#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Pillar_Small : public GameObject
	{
	public:

		Pillar_Small();
		~Pillar_Small();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
		float calculatedPosX;
	};
}


