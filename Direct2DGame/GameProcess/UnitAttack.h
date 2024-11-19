#pragma once

#include "MonoBehaviour.h"
class Unit;

/// <summary>
/// Unit의 공격을 담당하는 클래스이다.
/// </summary>
class UnitAttack :
    public MonoBehaviour
{
public:
    UnitAttack();
    ~UnitAttack();

public:
    void Update(float _deltaTime) override;
    void Attack(GameObject* _target);
    void Start() override;

private:
    // 총쏘기 
    void Shoot(GameObject* _target);

private:
    float m_attackCoolTime; // 공격 쿨타임

    ATTACK_TYPE m_attackType;
    float m_attackSpeed;
    Unit* m_unit;
};

