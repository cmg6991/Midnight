#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// 하녀 위치를 표시하는 컴포넌트 
/// 
/// </summary>
class CheckPosition :
    public MonoBehaviour
{
public:
    CheckPosition();
    ~CheckPosition();
    Component* Clone() override;

    void Start() override;
    void Render(D2DRenderer* _d2DRenderer) override;
public:
    bool Flip() const { return m_isFlip; }
    void SetFlip(bool val) { m_isFlip = val; }
    Vector2 m_offset;

private:
    int m_numbering;
    bool m_isFlip;
};

