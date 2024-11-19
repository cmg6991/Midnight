#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// 토끼에게 밀리는 박스
/// 
/// </summary>
class MovingCube :
    public MonoBehaviour
{
public:
    MovingCube();
    ~MovingCube();
    Component* Clone() override;

public:
    void OnCollisionStay(const Collision& _collision) override;


private:
    float m_pushSpeed; // 미는 속도

};

