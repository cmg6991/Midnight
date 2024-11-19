#pragma once
#include "UnitMovement.h"

/// <summary>
/// 공중유닛의 움직임
/// </summary>
class FlyMovement :
    public UnitMovement
{
public:
    FlyMovement();
    ~FlyMovement();

public:
    bool Move(float _deltaTime) override;
    
};

