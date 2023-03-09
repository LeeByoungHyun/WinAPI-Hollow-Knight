#pragma once
#include "yamyamEngine.h"

namespace ya
{
	class GameObject;
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Vector2 Calculate(Vector2 pos) { return pos - mDistance; }

	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;	// ī�޶��� ��ġ��ǥ
		static Vector2 mDistance;	// 
		static GameObject* mTarget;	// ī�޶��� ������ �Ǵ� ������Ʈ
	};
}


