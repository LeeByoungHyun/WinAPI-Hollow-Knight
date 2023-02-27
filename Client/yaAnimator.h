#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"
#include "yaImage.h"

namespace ya
{
	class Animator : public Component
	{
	public:
		// 
		struct Event
		{
			// 연산자 오퍼레이터
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
				{
					mEvent();
				}
			}

			// void(*name)(int, int)	// 함수포인터 기본문법
			std::function<void()> mEvent;	// functional 문법
		};

		// 
		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void CreateAnimation();	// 스프라이트 파일 한장에 다 모여있는 경우
		void Createanimations();	// 프레임별로 각각의 파일로 만들어진 경우

		Animation* FindAnimation(const std::wstring* name);
		void play(const std::wstring& name, bool loop);

		Events* FindEvents(const std::wstring& name);
		std::function<void>& GetStartEvent(const std::wstring& name);
		std::function<void>& GetCompleteEvent(const std::wstring& name);
		std::function<void>& GetEndEvent(const std::wstring& name);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Event*> mEvents;
		Animation* mActiveAnimation;
		Image* mSpriteSheet;
	};
}
