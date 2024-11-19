#pragma once


/// <summary>
/// 저장한 텍스트 파일을 불러오는 클래스
/// </summary>
class LoadFactory
{
public:
	LoadFactory(const ManagerSet* _managerSet);
	~LoadFactory();

	void Load(const wstring& _filePath);

	void CreateObject(int _index, Vector2 _position);
	
	vector<GameObject*>& GetContainer() { return m_objectContainer; }

	void SetPlayer(GameObject* val) { m_player = val; }
	void SetRabbit(GameObject* _rabbit) { m_rabbit = _rabbit; }
	void SetHp(GameObject* _hp) { m_hp = _hp; }
	void SetClearCheck(GameObject* val) { m_clearCheck = val; }

private:
	vector<GameObject*> m_objectContainer;
	GameObject* m_player;
	GameObject* m_rabbit;
	GameObject* m_clearCheck;
	GameObject* m_hp;
	const ManagerSet* m_managerSet;
};

