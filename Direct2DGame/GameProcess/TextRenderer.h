#pragma once
#include "Component.h"

class Transform;

/// <summary>
/// 텍스트를 랜더링하는 컴포넌트 
/// 
/// 2023.8.6 22:42 gitae
/// </summary>
class TextRenderer :
    public Component
{
public:
    TextRenderer();
    ~TextRenderer();
    Component* Clone() override;

    void Start() override;

    wstring GetPrintString() const { return m_printString; }
    void SetPrintString(const wstring& val) { m_printString = val; }
    Vector2 GetScale() const { return m_scale; }
    void SetScale(Vector2 val) { m_scale = val; }
    D2D1::ColorF GetColor() const { return m_color; }
    void SetColor(D2D1::ColorF val) { m_color = val; }
public:
    void Render(D2DRenderer* _d2DRenderer) override;

private:
    Transform* m_transform;
    wstring m_printString;
    Vector2 m_scale;
    ColorF m_color;
};

