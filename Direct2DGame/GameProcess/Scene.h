#pragma once

// 전방선언
class GameObject;
class ManagerSet;
class SceneManager;
class LightManager;

struct AddObjectInfomation
{
	GameObject* object;
	float delayTime;
};

/// <summary>
/// 씬을 구성하는 인터페이스이다 
/// 씬에 입장하기전에 Enter함수를 통해서 오브젝트들을 추가하고 여러가지 설정
/// </summary>
class Scene abstract
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet
		, SceneManager* _sceneManager);
	virtual void Finalize();

	// 씬에 들어가지전에 호출하는 함수
	virtual void Enter() = 0;
	// 씬에 나가기전에 호출하는 함수
	virtual void Exit();

public:
	void FixedUpdate(float _fixedDeltaTime);
	void Update(float deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DubugRender(D2DRenderer* _d2DRenderer);
	
	//후속 이벤트 처리
	void ProcessEvent(float _deltaTime);
	void AddMouse();
	void Start();

private:
	// 오브젝트들을 정렬한다.
	void SortObjectVector();
	void SortObjBySortingLayer();

public: 

	/// 씬에 오브젝트 추가를 요청
	void RegisterObject(GameObject* _object, float _delayTime)const;
	void RegisterNextScene(const wstring& _sceneName) const;

	const vector<GameObject*>& GetGroupObject(OBJECT_TYPE _type) const  
	{ return m_objectVector[static_cast<int>(_type)]; }

	vector<GameObject*>& GetUIGroupObject(OBJECT_TYPE _type) 
	{
		if (_type == OBJECT_TYPE::BACK_UI || _type == OBJECT_TYPE::FRONT_UI)
			return m_objectVector[static_cast<int>(_type)];
		else
		{
			assert(nullptr);
			return m_objectVector[static_cast<int>(_type)];
		}
	}


	wstring GetSceneName() const { return m_sceneName; }
	void SetSceneName(const wstring& val) { m_sceneName = val; }

protected:
	/// 자식오브젝트들도 같이 등록
	void AddObject(GameObject* _object); 
	void DestoryGroupObject(OBJECT_TYPE _type);
	const ManagerSet* GetManagerSet() { return m_managerSet; }

private:
	wstring m_sceneName; // 씬이름 

	SceneManager* m_scneneManager;
	D2DRenderer* m_d2DRenderer;
	ManagerSet* m_managerSet;

	// 씬이 오브젝트 타입에 따라서 오브젝트들을 관리한다.
	vector<GameObject*> m_objectVector[static_cast<int>(OBJECT_TYPE::END)];
	// 다음씬을 타입을 가진다 NONE타입이면 지정하지 않음
	mutable wstring m_nextScene;
	// 씬에 추가해야하는 오브젝트들을 추가하는 시간과 함께 가지고 있는다.
	mutable list<AddObjectInfomation> m_addObjectList;

};

