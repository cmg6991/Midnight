#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// 바 형태의 정보를 나타내는 UI
/// PostRender에서 랜더링을 한다.
/// 
/// 2023.7.16 13:25 gitae
/// </summary>
class BarUI :
    public MonoBehaviour
{
public:
    BarUI();
    ~BarUI();
    Component* Clone() override;

    void PostRender(D2DRenderer* _d2DRenderer) override;

    void SetBar(const BarUIInfo& _info);
    /// 0.f ~ 1.f로 현재의 바의 길이를 설정한다.
    void SetBarLength(float _barLen);

private:
    Vector2 m_positionOffset; // 객체와 떨어진 거리
    Vector2 m_innerBarOffset; // 내부 바와 외부 바의 크기 차이
    Vector2 m_scale; // 바의 크기 
    float m_barLength; // 현재 바의 길이 0.f ~ 1.f 사이

    D2D1::ColorF m_innerFillBarColor; // 내부를 채우는 바의 색
    D2D1::ColorF m_innerEmptyColor; // 내부바의 빈공간 바의 색
    D2D1::ColorF m_edgeColor;  // 가장자리 바의 색
};

