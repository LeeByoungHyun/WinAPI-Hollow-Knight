#pragma once
class SoulUI
{
};

#pragma once
#include "yaGameObject.h"

namespace ya
{
	class SoulUI : public GameObject
	{
	public:
		SoulUI();
		~SoulUI();

		// 싱글톤
		// 이미 인스턴스가 존재하면 인스턴스를 반환, 없다면 인스턴스 생성
		static SoulUI* GetInstance()
		{
			if (instance == nullptr)
				instance = new SoulUI();

			return instance;
		}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		float GetSoul() { return soul; }
		void SetSoul(float temp) { soul = temp; }

	private:
		class Player* mPlayer;
		class Image* mImage;
		class Image* temp;
		class Transform* tr;
		class Animator* mAnimator;

		class Scene* activeScene;
		float mTime = 0.0f;
		float soul = 100.0f;

		// 싱글톤 객체 인스턴스
		static SoulUI* instance;
	};
}


