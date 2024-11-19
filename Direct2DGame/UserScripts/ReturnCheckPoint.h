#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 플레이어가 체크 포인트를 기억하는 컴포넌트 
/// 
/// 
/// </summary>
class ReturnCheckPoint :
    public MonoBehaviour
{
public:
    ReturnCheckPoint();
    ~ReturnCheckPoint();
    Component* Clone() override;

public:
    // 플레이어를 체크 포인트로 순간이동 시킨다.
    void ReturnToCheckPoint();
    void SetCheckPoint(Vector2 _position, int _order);

private:
    Vector2 m_checkPoint; // 현재 체크포인트 위치 
    int m_checkPointOrder; // 체크포인트 순서

};

