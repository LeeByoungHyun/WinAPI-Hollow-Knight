#pragma once
#include "yaEntity.h"

namespace ya
{
	// 순수 가상함수를 하나라도 포함한 클래스는 추상클래스가 된다
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		// Resource를 상속받는 모든 클래스는 Load함수를 반드시 override해야 함
		virtual HRESULT Load(const std::wstring& path) = 0;	

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }

		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mKey;
		std::wstring mPath;

	};

}
