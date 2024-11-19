#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// 연출 트리거 기능을 한다
/// 
/// 이 컴포넌트를 가지는 오브젝트는 DirectManager에게 다음 연출을 지시한다.
/// 
/// </summary>
class ActirngTrigger :
    public MonoBehaviour
{
public:
    ActirngTrigger();
    ~ActirngTrigger();
    Component* Clone() override;

    
    void Set(int _actingNumber);
    void OnTriggerStay(const Collision& _collision) override;
    void DebugRender(D2DRenderer* _d2DRenderer) override;

private:
    int m_actingNumber; // 자신의 연출 순서
    bool m_isActive; // 활성화 상태인지 

};

