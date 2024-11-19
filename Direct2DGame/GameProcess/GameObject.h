#pragma once

#include "Component.h"

// 전방선언
class ManagerSet;
class InputManager;
class PathManager;
class SceneManager;
class TimeManager;
class UIManager;
class CollisionManager;
class CameraManager;
class DirectManager;
struct Collision;

/// <summary>
/// 오브젝트의 기본형
/// 컴포넌트 구조를 가진다
/// 
/// </summary>
class GameObject
{

public:
	/// 생성자 단계에서 오브젝트의 이름을 결정
	GameObject(const string& _name, const ManagerSet* _managerSet, OBJECT_TYPE _type);
	
	// 복사생성자
	GameObject(const GameObject& _other);

	virtual ~GameObject();

public:
	/// 삭제예정인 오브젝트인지
	bool IsAlive();

	// 씬에게 오브젝트 삭제요청을 한다.
	void Destory(float _destoryTime = 0.f);
	string GetName();
	const string& GetDebugName() { return m_name; }
	
	/// !!경고!! 오브젝를 삭제하고 싶으면 Destory를 사용
	void SetObjectState(OBJECT_STATE _state) { m_state = _state; }

	OBJECT_STATE GetObjectState() { return m_state; }
	void SetObjectType(OBJECT_TYPE _type) { m_type = _type; }
	OBJECT_TYPE GetObjectType() { return m_type; }
	bool IsActive() const { return m_isActive; }
	void SetActive(bool _isActive) { m_isActive = _isActive; }

	// 몇초후 삭제예정인지 반환
	float GetDestroyTime() { return m_destoryTime; }

	int GetSortingLayer() { return m_sortingLayer; }
	void SetSortingLayer(int _depth) { m_sortingLayer = _depth; }

public:
	void DestroyAllComponent();

	///  명시적 초기화
	void Start();
	void Finalize();

	/// 이벤트 함수 
	void FixedUpdate(float _fixedDeltaTime);
	void Update(float _deltaTime);
	void LateUpdate(float _deltaTime);
	void PreRender(D2DRenderer* _d2DRenderer);
	void Render(D2DRenderer* _d2DRenderer);
	void PostRender(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2dRenderer);

	// 물리엔진 함수  
	void IntergrateForces(float _fixedDeltaTime);

public:
	/// 카메라에 영향을 받는 오브젝트인지 
	bool IsCameraAffected() { return m_cameraAffected; }
	void SetCameraAffected(bool _isAffected) { m_cameraAffected = _isAffected; }

public:
	/// 자식 오브젝트 
	void AddChild(GameObject* _child);
	GameObject* GetChild(int _index);
	GameObject* GetChild(const string& _name);
	vector<GameObject*>& GetChildren();
	GameObject* GetParent();
	void SetParent(GameObject* _parent);

public: 
	/// 매니져 관련함수
	const ManagerSet* GetManagerSet()const { return m_managerSet; }
	const CameraManager* GetCameraManager()const;
	const PathManager* GetPathManager()const;
	const InputManager* GetInputManager()const;
	const TimeManager* GetTimeManager()const;
	const SceneManager* GetSceneManager()const;
	const UIManager* GetUIManager()const;
	const CollisionManager* GetCollisionManager()const;
	const DirectManager* GetDirectManager()const;
	const PhysicsManager* GetPhysicsManager()const;

	/// 마우스 입력 함수
	void OnMouse();
	void OnMouseUp();
	void OnMouseDown();
	void OnMouseClicked();

	/// 충돌 관련함수
	void OnCollisionEnter(const Collision& _collision);
	void OnCollisionExit(const Collision& _collision);
	void OnCollisionStay(const Collision& _collision);

	void OnTriggerEnter(const Collision& _collision);
	void OnTriggerStay(const Collision& _collision);
	void OnTriggerExit(const Collision& _collision);

	///Box2d 충돌 관련 함수

public:
	/// 컴포넌트 관련 함수 
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

private:
	/// Component을 호출순서대로 정렬해서 보관
	std::multimap<int, Component*> m_components; 

private:
	OBJECT_STATE m_state;
	OBJECT_TYPE m_type;
	bool m_isActive;

	float m_destoryTime;
	const string m_name;

	int m_sortingLayer;  // 화면에 출력될 순서 (defualt : 0)
	bool m_cameraAffected; // 카메라에 영향을 받는 오브젝트인지
	
	// 매니져 포인터 집합
	const ManagerSet* m_managerSet;
};

// 여기 한번더 감싸서 Component의 메모리 관리를 게임오브젝트가 하면 편리하지 않을까?? real루다가
// 그래서 컴포너트의 생성이 실패하면 메모리에 추가하지 않는거지!
// Add-> 메모리를 할당을 외부에서 하는걸로 하고 Create 접두사는 객체가 직접 메모리를 관리한다의 의미로 사용하자

template <typename T>
T* GameObject::CreateComponent()
{
	// 이미 생성된 컴포넌트는 생성하지 않음
	if (nullptr != GetComponent<T>())
	{
		return nullptr;
	}

	T* tmp = new T();
	Component* component = dynamic_cast<Component*>(tmp);

	// dynamic_cast를 했는데 Component가 아닌경우에는 nullptr 이므로 다시 삭제
	if (component == nullptr)
	{
		delete tmp;
		return nullptr;
	}

	// 컴포넌트와 게임 오브젝트 연결
	component->SetGameObject(this);

	// 게임오브젝의 multpmap에 정보 컴포넌트 삽입
	int callOreder = static_cast<int>(component->GetCallOrder());
	m_components.insert(make_pair(callOreder, component));

	return tmp;
}

template <typename T>
T* GameObject::GetComponent()
{ 
	for (auto& iter : m_components)
	{
		T* component = dynamic_cast<T*>(iter.second);
		if (component != nullptr)
		{
			return component;
		}
	}

	return nullptr;
}

// 일반화(템플릿)말고 추상화로 구현하면, 외부에서 GetComponent등으로 받을 때, 캐스팅을 해서 써야한다
// => Transform* transform = dynamic_cast<Transform*>(GetComponent(COMPONENT_TPYE::TRANSFORM)); -> 이런식으로 템플리이 더 편리한듯 ? 

