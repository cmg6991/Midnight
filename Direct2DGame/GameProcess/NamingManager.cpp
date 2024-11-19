#include "GameProcessPCH.h"
#include "NamingManager.h"

// 정적멤버 변수 초기화 
NamingManager* NamingManager::m_instance = nullptr;

NamingManager* NamingManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new NamingManager();
	}
	return m_instance;
}

void NamingManager::Finalize()
{
	delete this;
}

NamingManager::~NamingManager()
{
}

const string NamingManager::GenerateName(const string& _name)
{
	auto iter = m_nameInfo.find(_name);

	// 처음으로 생성된 이름
	if (iter == m_nameInfo.end())
	{
		m_nameInfo.insert(std::make_pair(_name, 1));
		return _name;
	}

	// 이미 생성한적 있는 이름이면 숫자를 붙여서 생성한다.
	int number = iter->second++;
	const string name = _name + std::to_string(number);

	return name;
}
