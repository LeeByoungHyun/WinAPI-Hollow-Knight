#pragma once
#include "yaGameObject.h"
#include "yaImage.h"

namespace ya
{
	class MenuGameStart : public GameObject
	{
	public:

		MenuGameStart();
		~MenuGameStart();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		Image* mImage;
		class Collider* mCollider;
		class Transform* tr;
		class Sound* buttonSound;
		double mTime = 0.0f;
		bool flag = false;

		class Menu_Pointer_L* pointerL;
		class Menu_Pointer_R* pointerR;
	};
}



