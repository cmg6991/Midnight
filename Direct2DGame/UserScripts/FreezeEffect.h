#pragma once
#include <MonoBehaviour.h>

class PlayerComponent;

/// <summary>
/// 플레이어의 언 효과를 도와주는 컴포넌트 
/// 
/// 
/// </summary>
class FreezeEffect :
    public MonoBehaviour
{
public:
    FreezeEffect();
    ~FreezeEffect();
    Component* Clone() override;

    void Start() override;
    void Update(float _deltaTime) override;
    void Freeze();

private:
    float m_freezeRatio; // 얼마나 얼었는지 0.f~ 1.f; 0에 가까울수록 파란색깔을 가짐

    bool m_isFreezing; // 얼었늦지
    float m_elapsedTime; 
    float m_freezeTime; // 지속시간

    Animator* m_animator;
    PlayerComponent* m_player;
    ParticleSystem* m_particleSystem;

    float m_defalutJumpPower;
    float m_defalutPlayerSpeed;
};

