#pragma once
#include <MonoBehaviour.h>

class PlayerComponent;

/// <summary>
/// 스탬프 컴포넌트 
/// 
/// 중력 상태에서는 눕고 
/// 비중력 상태에서는 일어난다.
/// 
/// </summary>
class Stamp :
    public MonoBehaviour
{
public:
    Stamp();
    ~Stamp();
    Component* Clone() override;

public:
    void Start() override;
    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;

    void SetPlayer(GameObject* _player) { m_player = _player; }

private:
    BoxCollider* m_boxCollider;
    GameObject* m_player;
    PlayerComponent* m_playerComponent;
    Transform* m_transform;

};

