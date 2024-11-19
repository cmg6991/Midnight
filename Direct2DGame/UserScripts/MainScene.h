#pragma once
#include <Scene.h>


/// <summary>
/// 게임의 메인 씬
/// </summary>
class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	void Enter() override;

};