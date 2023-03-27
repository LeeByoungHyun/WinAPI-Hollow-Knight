#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MantisLordsManager : public GameObject
	{
	public:
		MantisLordsManager();
		~MantisLordsManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class MantisLord1* mantisLord1;
		class MantisLord2* mantisLord2;
		class MantisLord3* mantisLord3;
	};
}


