#pragma once
#include "yaGameObject.h"

namespace ya
{
	class FalseObject02 : public GameObject
	{
	public:

		FalseObject02();
		~FalseObject02();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Transform* tr;
	};
}


