#pragma once

#include "Component.h"

class GameObject;
struct AABB;
struct Collision;
class CircleCollider;
class BoxCollider;
struct Node;

/// <summary>
/// 충돌체 인터페이스
/// </summary>
class Collider abstract
	:public Component
{
public:
	Collider(string _name, COLLIDER_TYPE _type);
	~Collider();

public:

	unsigned int GetID() const { return m_ID; }
	COLLIDER_TYPE GetColliderType() const { return m_type; }

	// 현재 충돌중인 충돌체 개수 반환
	int GetCurrentCollison() { return m_currentCollision; }

	/// 충돌체크관련함수 
	virtual bool Collides(Vector2 _position) = 0;
	virtual bool Collides(CircleCollider* _circle) = 0;
	virtual bool Collides(BoxCollider* _box) = 0;
	bool Collides(Collider* _collider);

	/// Broadphase 관련
	virtual Vector2 GetMinPoint()const = 0;
	virtual Vector2 GetMaxPoint()const = 0;

	Node* GetNode(){ return m_node;}
	void SetNode(Node* _node)
	{ m_node = _node; }

	/// 트리거 관련
	void SetTrigger(bool _isTrigger) { m_isTrigger = _isTrigger; }
	bool IsTrigger() const{ return m_isTrigger; }

	bool IsActive() const { return m_isActive; }
	void SetActive(bool _isActive) { m_isActive = _isActive; }

protected:
	int m_currentCollision; // 현재 충돌중이 충돌체 갯수 
private:
	// 충돌체의 아이디는 고유한 값을 가진다.
	const unsigned int m_ID;

	COLLIDER_TYPE m_type;

	// AABBTree에 해당하는 노드의 포인터를 type별로 가진다.
	Node* m_node;

	// 물리적 효과를 받지 않는 트리거 인지
	bool m_isTrigger; 
	bool m_isActive;
};

/// 콜라이더 충돌쌍을 가지고 Key값을 만든다
union ColliderKey
{
	ColliderKey(Collider* _c1, Collider* _c2) :Key(0)
	{
		ColliderID1 = FMath::Min(_c1->GetID(), _c2->GetID());
		ColliderID2 = FMath::Max(_c1->GetID(), _c2->GetID());
	}

	struct
	{
		unsigned int ColliderID1;
		unsigned int ColliderID2;
	};

	unsigned long long Key;
};

/// ColliderKey의 맵에서 사용하는 정렬알고리즘
inline bool operator <(const ColliderKey& c1, const ColliderKey& c2)
{
	if (c1.Key < c2.Key)
		return true;

	return false;
}