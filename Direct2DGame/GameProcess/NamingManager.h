#pragma once

/// <summary>
/// =디버그용도=
/// 오브젝트 네이밍을 해주는 전역 클래스
/// 싱글톤 패턴 사용
/// </summary>
class NamingManager
{
public:
	static NamingManager* GetInstance();
	void ClearNameInfo() { m_nameInfo.clear(); }
	void Finalize();
private:
	static NamingManager* m_instance;

private:
	NamingManager() = default;
	~NamingManager();
public:
	const string GenerateName(const string& _name);

private:
	// 이름정보들을 맵에 저장함 key : 오브젝트 이름 value : 오브젝트 생성 횟수
	map<const string, int> m_nameInfo;

};
