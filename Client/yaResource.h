#pragma once
#include "yaEntity.h"

namespace ya
{
	// ���� �����Լ��� �ϳ��� ������ Ŭ������ �߻�Ŭ������ �ȴ�
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		// Resource�� ��ӹ޴� ��� Ŭ������ Load�Լ��� �ݵ�� override�ؾ� ��
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
