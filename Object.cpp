#include "Object.h"

CObject::CObject(
	const std::wstring& objectName,
	const std::time_t& lastModifiedTime)
	: m_objectName(objectName),
	m_lastModifiedTime(lastModifiedTime)
{
}
