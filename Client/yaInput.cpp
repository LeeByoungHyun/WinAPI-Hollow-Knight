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
		// Ű���� Ű �ϳ��ϳ� ��Ī�Ͽ� mKeys vector�� �߰�
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
			// Ű ����
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� ���� �־��� ���
				if (mKeys[i].bePressed == true)
				{
					mKeys[i].state = eKeyState::Pressed;
				}

				// ���� �����ӿ��� ���� ���� �ʾ��� ���
				else
				{
					mKeys[i].state = eKeyState::Down;
				}

				mKeys[i].bePressed = true;

			}

			else // ���� �����ӿ� Ű�� �������� �ʴ�
			{
				// ���� �����ӿ��� ���� �־��� ���
				if (mKeys[i].bePressed == true)
				{
					mKeys[i].state = eKeyState::Up;
				}

				// ���� �����ӿ��� ���� ���� �ʾ��� ���
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