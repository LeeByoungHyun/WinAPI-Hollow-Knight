#include "yaImage.h"
#include "yaApplication.h"
#include "yaResourceManager.h"

// 다른 파일의 전역변수 사용
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

	Image* Image::Create(const std::wstring& name, UINT widht, UINT height)
	{
		if (widht == 0 || height == 0)
			return nullptr;

		Image* image = ResourceManager::Find<Image>(name);
		if (image != nullptr)
			return image;

		image = new Image();
		HDC mainHdc = application.GetHdc();

		image->mBitmap = CreateCompatibleBitmap(mainHdc, widht, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = widht;
		image->mHeight = height;

		image->SetKey(name);
		ResourceManager::Insert<Image>(name, image);

		return image;
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// c_str()은 배열 메모리의 시작 위치의 주소값을 반환

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
