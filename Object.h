#pragma once
#include <ctime>
#include <string>

class CObject
{
private:
	std::wstring m_objectName;
	std::time_t m_lastModifiedTime;

public:
	/**
	 * CObject
	 *
	 * Parametrized constructor
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] objectName       : Name of object
	 * @param[in] lastModifiedTime : Last modified time of object
	 */
	CObject(const std::wstring& objectName, const std::time_t& lastModifiedTime);

	/**
	 * getObjectName
	 *
	 * Get the name of object
	 *
	 * @author Rahul Naik
	 *
	 * @return string for object name
	 */
	std::wstring getObjectName()
	{
		return m_objectName;
	}

	/**
	 * getLastModifiedTime
	 *
	 * Get the last modified time of object
	 *
	 * @author Rahul Naik
	 *
	 * @return time_t for last modified time.
	 */
	std::time_t getLastModifiedTime()
	{
		return m_lastModifiedTime;
	}
};