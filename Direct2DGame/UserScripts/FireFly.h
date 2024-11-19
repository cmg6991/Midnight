#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 불빛파리 컴포넌트 
/// 
/// 
/// </summary>

enum class FIREFLY_STATE
{
    CURVE,
    CIRCLE,
    ETC,
};

class FireFly :
    public MonoBehaviour
{
public:
    FireFly();
    ~FireFly();
    Component* Clone() override;
    
public:
    void Start() override;
    void Update(float _deltaTime) override;
    void SetUp(Vector2 _distance, float _speed);
    void OnTriggerEnter(const Collision& _collision) override; 
    void DebugRender(D2DRenderer* _d2DRenderer) override;
    bool IsOnPlayer() { if (m_state == FIREFLY_STATE::CIRCLE) return true; else return false; }


private:
	Vector2 m_start;
	Vector2 m_end;
    Vector2 m_distance;
    Vector2 m_direction; //이동방향
    Vector2 position;
    bool m_isPositive; //정방향인지 아닌지
    float m_speed;
    float m_time;
    float m_rotation;

    GameObject* m_target;
    FIREFLY_STATE m_state;

};

