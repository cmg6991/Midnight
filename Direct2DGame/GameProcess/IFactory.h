#pragma once


class GameObject;
class ManagerSet;

/// <summary>
/// 팩토리의 인터페이스이다 
/// 인터페이스를 상속받아서 직접적이 개체들은 자식 클래스가 생성한다.
/// 
/// 인터페이스의 함수들은 자식쪽클래스의 생성을 도와준다. 
/// </summary>
class IFactory 
{
public:
	IFactory() = default;
	~IFactory();

public:
	// 가장기본적인 게임오브젝트를 생성한다 모든 게임오브젝트는 Trasform을 가진다.
	GameObject* CreateGameObject(const string& _name, const ManagerSet* _managerSet
		, OBJECT_TYPE _type, const TransformInfo& _info); 

	// 스케일이 zero인 경우 트랜스폼의 scale 값을 받아온다.
	void CreateBoxCollider(GameObject* _object, BoxColliderInfo _info);
	
	// 원형 콜라이더를 추가
	void CreateCircleColldier(GameObject* _object, CircleInfo _intfo);

	// 리지드 바디 추가 
	void CreateRigidBody(GameObject* _object, float _mass = 1.f);
	
	// 텍스처 랜더러를 추가
	void CreateTextureRenderer(GameObject* _object
		, const wstring& _key
		, Vector2 _offset = Vector2::Zero);
	
	// UI 컴포넌트 추가
	void CreateUI(GameObject* _object);


};

