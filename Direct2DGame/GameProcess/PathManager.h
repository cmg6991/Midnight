#pragma once


/// <summary>
/// 파일 경로를 받아오는 매니져 
/// static을 사용하긴 했는데 
/// 과연 메모리공간에 객체를 할당해야할까?
/// 모르겠다....
/// 
/// 다시보니 너무 쓸데없는거 같다 
/// </summary>
class PathManager 
{
public:
	PathManager();
	~PathManager();

	void Initalize();
	void Finalize();
	const wchar_t* GetRelativPath() const;

private:
	wchar_t m_relativePath[256];
};

