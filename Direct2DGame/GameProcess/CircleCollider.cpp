#include "GameProcessPCH.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "CollisionManager.h"

CircleCollider::CircleCollider()
	:Collider(typeid(this).name(),COLLIDER_TYPE::CIRCLE)
	,m_position{}
	,m_offset{}
	,m_radius(0.f)
{ 
}

CircleCollider::~CircleCollider()
{
}


Component* CircleCollider::Clone()
{
	CircleCollider* clone = new CircleCollider();

	clone->m_currentCollision = 0;
	clone->m_offset = m_offset;
	clone->m_radius = m_radius;
	clone->m_position = m_position;
	clone->SetTrigger(IsTrigger());

	return clone;
}

void CircleCollider::LateUpdate(float _deltaTime)
{
	Vector2 ownerPosition = GetComponent<Transform>()->GetPosition();
	m_position = ownerPosition + m_offset;
}

void CircleCollider::DebugRender(D2DRenderer* _d2DRenderer)
{

	if (m_currentCollision == 0)
	{
		_d2DRenderer->DrawEllipse(m_position, m_radius, D2D1::ColorF::LightGreen);
	}
	else
	{
		_d2DRenderer->DrawEllipse(m_position, m_radius, D2D1::ColorF::Red);
	}
}

void CircleCollider::OnCollisionEnter(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		++m_currentCollision;
}

void CircleCollider::OnCollisionExit(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		--m_currentCollision;
}

void CircleCollider::OnTriggerEnter(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		++m_currentCollision;
}

void CircleCollider::OnTriggerExit(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		--m_currentCollision;
}

bool CircleCollider::Collides(Vector2 _position)
{
	float distance = (m_position - _position).Length();

	if (distance <= m_radius)
		return true;

	return false;
}

bool CircleCollider::Collides(CircleCollider* _circle)
{
	// 원과 원의 충돌

	Vector2 leftPosition = GetPosition();
	float leftRadius = GetRadius();

	Vector2 rightPosition = _circle->GetPosition();
	float rightRaius = _circle->GetRadius();

	float distance = (leftPosition - rightPosition).Length();

	if (distance <= rightRaius + leftRadius)
	{
		return true;
	}

	return false;
}

bool CircleCollider::Collides(BoxCollider* _box)
{
	return _box->Collides(this);
}

Vector2 CircleCollider::GetMinPoint() const 
{
	return Vector2(m_position.x - m_radius, m_position.y - m_radius);
}

Vector2 CircleCollider::GetMaxPoint() const 
{
	return Vector2(m_position.x + m_radius, m_position.y + m_radius);
}

