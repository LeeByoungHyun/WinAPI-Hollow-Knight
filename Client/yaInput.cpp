#include "yaInput.h"

namespace ya
{
	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_SPACE,
	};

	std::vector <Input::Key> Input::mKeys;

	void Input::Initialize()
	{
		// 키보드 키 하나하나 매칭하여 mKeys vector에 추가
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bePressed = false;

			mKeys.push_back(keyInfo);
		}
	}

	void Input::Update()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			// 키 눌림
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// 이전 프레임에서 눌려 있었을 경우
				if (mKeys[i].bePressed == true)
				{
					mKeys[i].state = eKeyState::Pressed;
				}

				// 이전 프레임에서 눌려 있지 않았을 경우
				else
				{
					mKeys[i].state = eKeyState::Down;
				}

				mKeys[i].bePressed = true;

			}

			else // 현재 프레임에 키가 눌려있지 않다
			{
				// 이전 프레임에서 눌려 있었을 경우
				if (mKeys[i].bePressed == true)
				{
					mKeys[i].state = eKeyState::Up;
				}

				// 이전 프레임에서 눌려 있지 않았을 경우
				else
				{
					mKeys[i].state = eKeyState::None;
				}

				mKeys[i].bePressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}
}