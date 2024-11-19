#pragma once
#include <Scene.h>

/// <summary>
/// 예시용 씬
/// </summary>
class ExampleScene : public Scene
{
public:
    ExampleScene();
    ~ExampleScene();

public:
    /// 씬에서 루프를 시작하기전에 호출하는 함수
    void Enter() override;
};

