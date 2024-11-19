#pragma once

#include "Collider.h"

class GameObject;
class InputManager;
/// <summary>
/// 원형 콜라이더 
/// 
/// </summary>
class CircleCollider :public Collider
{
public:
	CircleCollider();
	~CircleCollider();
	Component* Clone() override;

public:
	/// 이벤트 관련
	void LateUpdate(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

public:
	void SetPosition(Vector2 _position) { m_position = _position; }
	void SetOffset(Vector2 _offset) { m_offset = _offset; }
 	void SetRadius(float _raidus) { m_radius = _raidus; }

	Vector2 GetOffset() { return m_offset; }
	Vector2 GetPosition() { return m_position; }
	float GetRadius() { return m_radius; }


	/// 충돌체 카운트 관련
	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;

	void OnTriggerEnter(const Collision& _collision) override;
	void OnTriggerExit(const Collision& _collision) override;

public:
	bool Collides(Vector2 _position) override;
	bool Collides(CircleCollider* _circle) override;
	bool Collides(BoxCollider* _box) override;

public:
	Vector2 GetMinPoint() const override;
	Vector2 GetMaxPoint() const override;

private:
	Vector2 m_offset;
	Vector2 m_position; 

	float m_radius;
};

