#pragma once
#include <MonoBehaviour.h>

/// <summary>
///  마지막 연출 컴포넌트 
/// </summary>
class FinalAct :
    public MonoBehaviour
{
public:
    FinalAct();
    ~FinalAct();
    Component* Clone() override;

public:

    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;
    void OnMouseClicked() override;

   
private:
    bool m_isStart;
    int m_index;
    float m_ratio;
    
};
