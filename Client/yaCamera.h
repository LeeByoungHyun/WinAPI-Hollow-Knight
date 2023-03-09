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
		static Vector2 mLookPosition;	// 카메라의 위치좌표
		static Vector2 mDistance;	// 
		static GameObject* mTarget;	// 카메라의 기준이 되는 오브젝트
	};
}


