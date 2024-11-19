
#include "Component.h"

class Transform;

/// <summary>
/// 포인트라이트 랜더러 컴포넌트
/// 
/// </summary>
class PointLightRenderer :
    public Component
{
public:
    PointLightRenderer();
    ~PointLightRenderer();
    Component* Clone() override;

    void Start() override;
    void Update(float _deltaTime) override;
    void PreRender(D2DRenderer* _d2DRenderer) override;
    void Render(D2DRenderer* _d2DRenderer) override;
    void PostRender(D2DRenderer* _d2DRenderer) override;

    D2D1_VECTOR_3F GetRGB() const { return m_rgb; }
    // Vector3 x,y,z 각각 r,g,b 에 대응한다.
    void SetRGB(D2D1_VECTOR_3F val) { m_rgb = val; }
    void SetRGB(int color);

    float GetIntensity() const { return m_maxIntensity; }
    void SetIntensity(float val) { m_maxIntensity = val; }
    RENDERING_MODE GetRederingMode() const { return m_mode; }
    void SetRenderingMode(RENDERING_MODE val) { m_mode = val; }

    Vector2 GetScale() const { return m_scale; }
    void SetScale(Vector2 val) { m_scale = val; }
    float GetAngle() const { return m_angle; }
    void SetAngle(float val) { m_angle = val; }
    float GetMinimumIntensity() const { return m_minimumIntensity; }
    void SetMinimumIntensity(float val) { m_minimumIntensity = val; }
    bool IsFixedIntensity() const { return m_isFixedIntensity; }
    void SetFixedIntensity(bool val) { m_isFixedIntensity = val; }
    float GetIntensityChangeSpeed() const { return m_intensityChangeSpeed; }
    void SetIntensityChangeSpeed(float val) { m_intensityChangeSpeed = val; }
    Vector2 GetOffset() const { return m_offset; }
    void SetOffset(Vector2 val) { m_offset = val; }
    bool IsLightOn() const { return m_isLightOn; }
    void SetLightOn(bool val) { m_isLightOn = val; }
private:
    void PointLightRender(D2DRenderer* _renderer);

private:
    Transform* m_transform;
    RENDERING_MODE m_mode; // 랜더링 순서
    D2D1_VECTOR_3F m_rgb; // rgb 컬러
    float m_currentIntensity; // 현재 밝기
    float m_maxIntensity; // 가장 높은 밝기
    float m_minimumIntensity; // 가장 낮은 밝기
    Vector2 m_scale; 
    Vector2 m_offset;
    float m_angle;

    bool m_isLightOn;
    bool m_isIncrease; 
    bool m_isFixedIntensity; // 밝기를 고정해서 사용하는지 
    float m_intensityChangeSpeed;  // 밝기 변화 속도
};
