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
		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		static void SetLookPosition(Vector2 pos) { mLookPosition = pos; }

		static void SetMinX(float f) { MinX = f; }
		static void SetMaxX(float f) { MaxX = f; }
		static void SetMinY(float f) { MinY = f; }
		static void SetMaxY(float f) { MaxY = f; } 

	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;	// 카메라의 위치좌표
		static Vector2 mDistance;	// 
		static GameObject* mTarget;	// 카메라의 기준이 되는 오브젝트

		static float MinX;
		static float MaxX;
		static float MinY;
		static float MaxY;
	};
}


