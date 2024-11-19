#pragma once

#include "Component.h"

/// <summary>
/// 위치,크기를 관리하는 컴포넌트이다
/// 
/// + 부모 자식관계도 관리한다 23.06.29
/// 
/// 
/// </summary>
class Transform : public Component
{
public:
	Transform();
	~Transform();
	Component* Clone() override;

public:
	/// 이벤트 관련 함수
	void LateUpdate(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	/// 트랜스폼 관련 
	void SetPosition(Vector2 _position) { m_position = _position; }
	void SetRotation(float _radian);
	void SetScale(Vector2 _scale) { m_scale = _scale; }

	void AddRotation(float _radian);
	void AddPosition(Vector2 _addPosition) { m_position += _addPosition; }

	Vector2 GetPosition() { return m_position; }
	Vector2 GetScale() { return m_scale; }
	float GetRotation() { return m_rotation; }

public:
	/// 부모 자식관계 
	GameObject* GetParent() { return m_parent; }
	
	// 모든 자식을 반환
	vector<GameObject*>& GetChildren() { return m_children; }
	GameObject* GetChild(int _index);
	GameObject* GetChild(const string& _name);
	
	/// 자식 오브젝트 추가
	void AddChild(GameObject* _child);
	void SetParent(GameObject* _parent);
	 
	// 부모 오브젝트와의 위치 차이를 설정
	void SetOffset(const Vector2& _position) { m_positionOffset = _position; }
	// 부모 오브젝트와 회전 차이를 설정
	void SetOffset(const float& _rotation) { m_rotationOffset = _rotation; }
	
	Vector2 GetPositionOffset() { return m_positionOffset; }
	float GetRotationOffset() { return m_rotationOffset; }
private:
	// 부모오브젝의 위치에 따라서 자식 오브젝트의 위치를 조정하는 함수
	void AlignParentPosition();

private:
	Vector2 m_position;
	float m_rotation;
	Vector2 m_scale;

	// 부모 자식 관계를 트랜스 폼에서 관리한다.
	Vector2 m_positionOffset;
	float m_rotationOffset;

	GameObject* m_parent;
	vector<GameObject*> m_children;
};
