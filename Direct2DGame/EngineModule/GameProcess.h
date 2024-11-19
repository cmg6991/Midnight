#pragma once
#include "IGameProcess.h"

/// <summary>
/// 게임 진행을 담당하는 클래스이다 
/// GameProcess 프로젝트를 가지고 관리한다. 
///
/// </summary>
class GameProcess :
	public IGameProcess
{
public:
	GameProcess();
	~GameProcess();

	void Initalize(D2DRenderer* _d2DRenderer, HWND _main) override;
	void Process() override;
	void Finalize() override;

	bool IsGameRunning() override { return m_gameRunnig; }
	void EndGame() { m_gameRunnig = false; }

private:
	bool ShowDubg();

private:
	/// 현재 게임 프로세스가 진행판단
	bool m_gameRunnig;


	bool m_showDebug;	/// 이번 프레임에 디버그 정보를 표시하는지
	float m_elapsedTime;

	HWND m_hWnd;	// 메인 윈도우 핸들 
	D2DRenderer* m_d2DRenderer;	// 랜더러

	Vector2 m_screenSize;

	// 매니져 집합
	ManagerSet* m_managerSet;

	// 매니져 
	CameraManager* m_cameraManager;
	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	CollisionManager* m_collisionManager;
	PathManager* m_pathManager;
	UIManager* m_UIManager;
	ResourceManager* m_resourceManager;
	DirectManager* m_directManager;
};
