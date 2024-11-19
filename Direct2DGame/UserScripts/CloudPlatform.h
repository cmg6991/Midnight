#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// 둥실 둥실 떠다니는 걸 도와주는 컴포넌트
/// 
/// 
/// </summary>
class CloudPlatform :
    public MonoBehaviour
{
public:
    CloudPlatform();
    ~CloudPlatform();
    Component* Clone() override;

    void Start() override;
    void Update(float _deltaTime) override;
    
    void OnCollisionStay(const Collision& _collision) override;
    
public:
    float m_moveSpeed; // 이동속도 
    Vector2 m_startPosition;
    Vector2 m_endPosition;
    Transform* m_transform;
    bool m_positive;
};

