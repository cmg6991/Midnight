#pragma once

#include "Scene.h"

/// <summary>
/// 스타트 컷씬 연출이 들어간다. 
/// 
/// 
/// </summary>
class StartCutScene : public Scene
{
public:
	StartCutScene();
	~StartCutScene();

private:
	void Enter() override;

		
};

