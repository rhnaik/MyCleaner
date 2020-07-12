#pragma once
#include <ctime>
#include <string>

class CObject
{
private:
	std::wstring m_objectName;
	std::time_t m_lastModifiedTime;

public:
	std::wstring getObjectName()
	{
		return m_objectName;
	}

	std::time_t getLastModifiedTime()
	{
		return m_lastModifiedTime;
	}

	CObject(const std::wstring& objectName, const std::time_t& lastModifiedTime);
};