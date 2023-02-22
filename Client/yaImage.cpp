#include "yaImage.h"
#include "yaApplication.h"

// �ٸ� ������ �������� ���
extern ya::Application application;

namespace ya
{
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
		/*
		mBitmap = NULL;
		mHdc = NULL;
		mWidth = 0;
		mHeight = 0;
		*/
	}

	Image::~Image()
	{

	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// c_str()�� �迭 �޸��� ���� ��ġ�� �ּҰ��� ��ȯ

		if (mBitmap == nullptr)
		{
			return E_FAIL;	// 0
		}

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}
}
