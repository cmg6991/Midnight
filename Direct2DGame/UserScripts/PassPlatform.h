#pragma once
#include <MonoBehaviour.h>

class PlayerComponent;
class RabbitComponent;

/// <summary>
/// 통과 가능한 플랫폼 컴포넌트
/// 
/// 중력   : 아래에서는 통과가 가능하고 위에서는 통과가 불가능하다.
/// 역중력 : 아래에서는 통과가 불가능하고 위에서는 통과가 가능하다.
/// </summary>
class PassPlatform :
    public MonoBehaviour
{
public:
    PassPlatform();
    ~PassPlatform(); 
    Component* Clone() override;

    void Start() override;
    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;


    void SetPlayer(GameObject* _player) { m_player = _player; }
    void SetRabbit(GameObject* _rabbit) { m_rabbit = _rabbit; }
private:
    GameObject* m_player;
    GameObject* m_rabbit;
    PlayerComponent* m_playerComponent;
    RabbitComponent* m_rabbitComponent;
    BoxCollider* m_playerBox;
    BoxCollider* m_rabbitBox;
    BoxCollider* m_platformBox;
    
    TextureRenderer* m_renderer;

    const float OFFSET = 0.1f;
};