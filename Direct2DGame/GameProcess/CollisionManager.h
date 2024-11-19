#pragma once

// 전방선언
class Collider;
class InputManager;
class SceneManager;
class GameObject;
class AABBTree;
union ColliderKey;


// 충돌처리에 필요한 정보를 가진다.
struct CollisionInfomation
{
	CollisionInfomation(Collider* _collider1, Collider* _collider2
		, bool _prev, bool _current)
		:collider1(_collider1)
		, collider2(_collider2)
		, prevCollision(_prev)
		, currentCollision(_current)
	{}

	Collider* collider1;
	Collider* collider2;
	
	bool prevCollision; // 이전프레임 충돌 정보
	bool currentCollision; // 현재 프레임 충돌 정보
};

/// <summary>
///  충돌을 관리하는 매니져이다.
/// 추가기능으로는 다양한 collider를 구현하고 
/// 그에 맞게 매니져는 collider의 종류에 따라서 
/// 충돌정보를 생성하고 전달해준다.
/// </summary>
class CollisionManager
{
public:
	// ColliderID를 발급하는 함수
	static unsigned int GetColliderID() { static unsigned int ID = 0; return ID++; }  

public:
	CollisionManager();
	~CollisionManager();

	void Initalize(InputManager* _inputManager, SceneManager* _sceneManager);
	void Update();
	void Finalize();

	void DebugRender(D2DRenderer* _d2DRenderer);

	// 두 오브젝트가 충돌하는 타입인지 반환하는 함수
	bool IsCollisionType(Collider* _left, Collider* _right);
public:
	// 오브젝트 타입과 타입간의 충돌설정을 한다.
	void CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const;
	void OffCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right)const;

	// AABB Tree에 새로운 콜라이더 추가
	void AddColider(Collider* _collider) const;
	
	// 씬을 변경할때, 게임이 종료할때 호출
	void Clear();

public:
	// 점과 충돌하는 모든 충돌체 반환
	void DetectPointToCollider(const Vector2& _point, vector<Collider*>& _colliderVector) const;

	// 박스와 충돌하는 모든 충돌체를 반환한다.
	void DetectBoxToCollider(const Vector2& _minPoint, const Vector2& _maxPoint, vector<Collider*>& _colliderVector) const;

	int GetCheckType(OBJECT_TYPE _type)const { return m_collisionCheck[static_cast<int>(_type)]; }

private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

	// Boradphase 알고리즘 
	AABBTree* m_aabbTree; 
	// 이전 프레임, 현재 프레임 충돌정보들을 저장
	map<ColliderKey, CollisionInfomation> m_collisionInfomations;

	// 오브젝트 타입별로 충돌을 판단 const 매니져에서 수정가능하게 mutable로 오픈
	mutable int m_collisionCheck[static_cast<int>(OBJECT_TYPE::END)];
};

