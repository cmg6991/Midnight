#pragma once
#include <Scene.h>


/// <summary>
///  명기의 작업공간 
/// 
/// 
/// </summary>
class 명기Scene :
    public Scene 
{
public:
    명기Scene();
    ~명기Scene();

public:
    void Enter() override;

};

