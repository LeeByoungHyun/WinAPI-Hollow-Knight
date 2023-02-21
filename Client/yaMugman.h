#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Mugman : public GameObject
	{
	public:

		Mugman();
		~Mugman();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	};

}

