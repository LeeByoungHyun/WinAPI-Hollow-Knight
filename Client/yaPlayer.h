#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			Idle,
			Walk,
			Jump,
			Fall,
			Dash,
			Slash,
			SlashAlt,
			UpSlash,
			Recoil,
			Focus,
			FocusEnd,
			FocusGet,
			FocusGetOnce,
			Death,
			CastFireball
		};

		enum class eDirection
		{
			Left,
			Right
		};

		Player();
		~Player();

		// 이미 인스턴스가 존재하면 인스턴스를 반환, 없다면 인스턴스 생성
		static Player* GetInstance()
		{
			if (instance == nullptr)
				instance = new Player();

			return instance;
		}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		int GetAtk() { return atk; }


	private:
		void idle();
		void walk();
		void slash();
		void slashAlt();
		void upSlash();
		void dash();
		void jump();
		void fall();
		void castFireball();
		void recoil();
		void death();
		void focus();
		void focusEnd();
		void focusGet();
		void focusGetOnce();

		void slashEndEvent();
		void slashAltEndEvent();
		void upSlashEndEvent();
		void recoilEndEvent();
		void dashEndEvent();
		void deathEndEvent();
		void focusEndEvent();
		void focusEndEndEvent();
		void focusGetEndEvent();
		void focusGetOnceEndEvent();
		void castFireballEndEvent();


	private:
		class Transform* tr;
		class Animator* mAnimator;
		class Scene* curScene;
		class RigidBody* mRigidBody;
		class Collider* mCollider;

		ePlayerState mState;
		eDirection mDirection = eDirection::Right;

		int hp;
		int atk = 1;
		double mTime = 0.0f;

		bool idleFlag			= false;
		bool walkFlag			= false;
		bool slashFlag			= false;
		bool slashAltFlag		= false;
		bool upSlashFlag		= false;
		bool dashFlag			= false;
		bool deathFlag			= false;
		bool invincibilityFlag	= false;
		bool focusFlag			= false;
		bool focusEndFlag		= false;
		bool focusGetFlag		= false;
		bool focusGetOnceFlag	= false;
		bool castFireballFlag	= false;
		bool jumpFlag			= false;
		bool doubleJumpFlag		= false;
		
		// 싱글톤
		//Player();
		//Player(const Player& other);
		//~Player();

		static Player* instance;
	};
}



