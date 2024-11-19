#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// Æ©Åä¸®¾ó Å° ÄÄÆ÷³ÍÆ®
/// 
/// </summary>
class TutorialKey :
    public MonoBehaviour
{
public:
    TutorialKey();
    ~TutorialKey();
    Component* Clone() override;


    void Start() override;
    void Update(float _deltaTime) override;


public:
    void SetPlayer(GameObject* val) { m_player = val; }

private:
    GameObject* m_player;
    
    TextureRenderer* m_renderer;

};

