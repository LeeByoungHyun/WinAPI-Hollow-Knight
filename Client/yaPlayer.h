#pragma once
#include "yaGameObject.h"
#include "yaTransform.h"

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
			DoubleJump,
			Fall,
			Dash,
			Slash,
			SlashAlt,
			UpSlash,
			DownSlash,
			Recoil,
			Spike,
			Focus,
			FocusEnd,
			FocusGet,
			FocusGetOnce,
			Death,
			CastFireball,
			Enter,
			WakeUp,
			WallSlide,
			WallJump,
			Challenge,
			Skull
		};

		enum class eDirection
		{
			Left,
			Right
		};

		Player();
		~Player();

		// 싱글톤
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

		int GetNeilAtk() { return neilAtk; }
		int GetSpellAtk() { return spellAtk; }
		Vector2 GetPos() { return tr->GetPos(); }
		void SetPos(Vector2 pos) { tr->SetPos(pos); }
		ePlayerState GetPlayerState() { return mState; }
		void SetPlayerState(ePlayerState state) { mState = state; }
		eDirection GetPlayerDirection() { return mDirection; }
		int GetHp() { return hp; }
		void SetHP(int n) { hp = n; }

		bool GetIdleFlag() { return idleFlag; }
		void SetIdleFlag(bool flag) { idleFlag = flag; }
		void SetFallFlag(bool flag) { fallFlag = flag; }

		bool GetEnterComplateFlag() { return enterComplateFlag; }
		bool GetChallengeComplateFlag() { return challengeCompleteFlag; }

	private:
		void idle();
		void walk();
		void slash();
		void slashAlt();
		void upSlash();
		void downSlash();
		void dash();
		void jump();
		void doubleJump();
		void fall();
		void castFireball();
		void recoil();
		void spike();
		void death();
		void focus();
		void focusEnd();
		void focusGet();
		void focusGetOnce();
		void enter();
		void wakeUp();
		void wallSlide();
		void wallJump();
		void challenge();
		void skull();

		void slashEndEvent();
		void slashAltEndEvent();
		void upSlashEndEvent();
		void downSlashEndEvent();
		void recoilEndEvent();
		void spikeCompleteEvent();
		void dashEndEvent();
		void deathEndEvent();
		void focusEndEvent();
		void focusEndEndEvent();
		void focusGetEndEvent();
		void focusGetOnceEndEvent();
		void castFireballEndEvent();
		void doubleJumpEndEvent();
		void enterComplateEvent();
		void wakeUpCompleteEvent();
		void wallJumpCompleteEvent();
		void challengeComplateEvent();

		void initializeFlag();

	private:
		class Transform* tr;
		class Animator* mAnimator;
		class Scene* curScene;
		class RigidBody* mRigidBody;
		class Collider* mCollider;

		ePlayerState mState;
		eDirection mDirection = eDirection::Right;

		int hp;
		int neilAtk;
		int spellAtk;
		double mTime = 0.0f;

		bool idleFlag			= false;
		bool walkFlag			= false;
		bool slashFlag			= false;
		bool slashAltFlag		= false;
		bool upSlashFlag		= false;
		bool downSlashFlag		= false;
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
		bool fallFlag			= false;
		bool stunFlag			= false;
		bool recoilFlag			= false;
		bool enterFlag			= false;
		bool enterComplateFlag	= false;
		bool spikeFlag			= false;
		bool wakeUpFlag			= false;
		bool wallSlideFlag		= false;
		bool wallJumpFlag		= false;
		bool challengeFlag		= false;
		bool challengeCompleteFlag	= false;
		bool challengeSoundFlag = false;
		bool skullFlag = false;

		// sound
		class Sound* walkSound;
		class Sound* damageSound;
		class Sound* dashSound;
		class Sound* doubleJumpSound;
		class Sound* fireballSound;
		class Sound* jumpSound;
		class Sound* landSound;
		class Sound* focusChargeSound;
		class Sound* focusSuccessSound;
		class Sound* slash1Sound;
		class Sound* slash2Sound;
		class Sound* slash3Sound;
		class Sound* slash4Sound;
		class Sound* slash5Sound;
		class Sound* challengeSound;

		// 싱글톤 객체 인스턴스
		static Player* instance;
	};
}



