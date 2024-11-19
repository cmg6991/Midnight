#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
	:m_relativePath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::Initalize()
{
	GetCurrentDirectoryW(255, m_relativePath);
	int iLen = (int)wcslen(m_relativePath);
	// 상위 폴더로
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_relativePath[i])
		{
			m_relativePath[i] = '\0';
			break;
		}
	}
}

void PathManager::Finalize()
{

}

const wchar_t* PathManager::GetRelativPath() const
{

	return m_relativePath;
}
