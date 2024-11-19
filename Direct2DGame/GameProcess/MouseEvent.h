#pragma once
#include "Component.h"

/// <summary>
/// UI관련 컴포넌트 
/// 마우스 입력에 관한 함수 호출을 담당한다.
/// 
/// </summary>
class MouseEvent :
    public Component
{
public:
    MouseEvent();
    ~MouseEvent();

    Component* Clone() override;

public:
    void LateUpdate(float _deltaTime) override;
    
    bool IsMouseOn() { return m_mouseOn; }
    bool IsLBtnDown() { return m_LBtnDown; }

    void DebugRender(D2DRenderer* _d2DRenderer) override;

    void SetMouseOn(bool _isMouseOn) { m_mouseOn = _isMouseOn; }
    void SetLBtnDown(bool _isLBtnDown) { m_LBtnDown = _isLBtnDown; }
private:
    bool m_mouseOn; // UI 위에 마우스가 있는지
    bool m_LBtnDown; // UI에 왼쪽 마우스 버튼이 눌린적이 있는지

};
 
