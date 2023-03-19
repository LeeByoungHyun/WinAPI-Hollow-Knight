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
		static Vector2 mLookPosition;	// ī�޶��� ��ġ��ǥ
		static Vector2 mDistance;	// 
		static GameObject* mTarget;	// ī�޶��� ������ �Ǵ� ������Ʈ

		static float MinX;
		static float MaxX;
		static float MinY;
		static float MaxY;
	};
}


