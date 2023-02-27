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
			// ������ ���۷�����
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

			// void(*name)(int, int)	// �Լ������� �⺻����
			std::function<void()> mEvent;	// functional ����
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

		void CreateAnimation();	// ��������Ʈ ���� ���忡 �� ���ִ� ���
		void Createanimations();	// �����Ӻ��� ������ ���Ϸ� ������� ���

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
