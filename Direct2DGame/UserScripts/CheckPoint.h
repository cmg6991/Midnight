#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// 체크 포인트를 담당하는 컴포넌트
/// 
/// 
/// 2023.8.12 23:16 gitae
/// </summary>
class CheckPoint :   public MonoBehaviour
{
public:
	CheckPoint();
	~CheckPoint();
	Component* Clone() override;
	
	void Start() override;

public:
	void OnTriggerEnter(const Collision& _collision) override;

	int GetOrder() const { return m_order; }
	void SetOrder(int _order) { m_order = _order; }
private:
	int m_order;
	Vector2 m_position;
};

