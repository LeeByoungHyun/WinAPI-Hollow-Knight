#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Mantis_Cage_T : public GameObject
	{
	public:

		Mantis_Cage_T();
		~Mantis_Cage_T();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


