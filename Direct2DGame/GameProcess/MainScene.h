#pragma once
#include "Scene.h"
class MainScene :
    public Scene
{
public:
    MainScene();
    ~MainScene() override;

public:
    void Enter() override;
};

