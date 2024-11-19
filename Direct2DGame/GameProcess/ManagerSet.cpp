#include "GameProcessPCH.h"
#include "ManagerSet.h"
#include "DirectManager.h"


ManagerSet::~ManagerSet()
{

}

void ManagerSet::Initalize(PathManager* _pathManager,
	InputManager* _inputManager,
	TimeManager* _timeManager,
	SceneManager* _sceneManager,
	UIManager* _UIManager,
	CollisionManager* _collisionManager,
	CameraManager* _cameraManager,
	DirectManager* _directManager
	)
{
	/// 매니져들 받아오기
	m_pathManager = _pathManager;
	m_inputManager = _inputManager;
	m_sceneManager = _sceneManager;
	m_UIManager = _UIManager;
	m_collisionManager = _collisionManager;
	m_cameraManager = _cameraManager;
	m_directManager = _directManager;
	m_timeManager = _timeManager;
 
}
