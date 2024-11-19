#pragma once
#include "Component.h"

class Transform;

/// <summary>
/// 텍스처를 랜더링하는 컴포넌트이다 
/// 
/// 텍스처 랜더링은 키값만으로 자세한 정보는 
/// 랜더러가 들고있는 형태이다.
/// </summary>
class TextureRenderer :
    public Component
{
public:
    TextureRenderer();
    ~TextureRenderer();
    Component* Clone() override;

    void Render(D2DRenderer* _d2DRenderer) override;
    void Start() override;

    void SetKey(const wstring& _key) { m_textKey = _key; }
    void SetOffset(const Vector2& _offset) { m_offset = _offset; }
    void SetXOffset(const float& _offset) { m_offset.x = _offset; }
    void SetYOffset(const float& _offset) { m_offset.y = _offset; }


    const wstring GetKey() { return m_textKey; }
    const Vector2& GetOffset() { return m_offset; }

    void SetAlpha(float _alpha) 
    {
        m_alpha = FMath::Clamp(_alpha, 0.f, 1.f); 

     }
    float GetAlpha() { return m_alpha; }

    Vector2 GetScale() const { return m_scale; }
    void SetScale(Vector2 val) { m_scale = val; }

    FLIP_TYPE GetFlipType() const { return m_flipType; }
    void SetFlipType(FLIP_TYPE val) { m_flipType = val; }
private:
    wstring m_textKey;// 랜더링하는 텍스트 이미지 Key값
	Vector2 m_offset;    // 오브젝트와의 오프셋
    Vector2 m_scale;
    float m_alpha;// 투명도 
    FLIP_TYPE m_flipType; // 좌우 상하 반전 타입
    Transform* m_transform;
};

