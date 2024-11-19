#pragma once
#include <Scene.h>

/// <summary>
///  마지막 스테이지 
/// 
/// </summary>
class Stage03 :
    public Scene
{
public:
    Stage03();
    ~Stage03();
    
private:
    void Enter() override;

};

