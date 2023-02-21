#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MessageOnCursur : public GameObject
	{
	public:
		MessageOnCursur();
		~MessageOnCursur();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	};
}


