#include "GameProcessPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "ManagerSet.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "UIManager.h"
#include "DirectManager.h"
#include "NamingManager.h"

SceneManager::SceneManager()
	:m_currentScene(nullptr)
	,m_d2DRenderer(nullptr)
	,m_gameRun(false)
	,m_managerSet(nullptr)
	,m_collisionManager(nullptr)
	,m_directManager(nullptr)
	,m_isPause(false)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initalize(D2DRenderer* _d2DRenderer
	, ManagerSet* _managerSet, CollisionManager* _collisionManager
	, DirectManager* _directManager, map<wstring, Scene*> _sceneContainer
	, const wstring& _startScene)
{
	m_gameRun = true;
	m_d2DRenderer = _d2DRenderer;
	m_managerSet = _managerSet;
	m_collisionManager = _collisionManager;
	m_directManager = _directManager;
	m_sceneCotainer = std::move(_sceneContainer);

	// 명시적 초기화
	for (auto& scene : m_sceneCotainer)
	{
		scene.second->Initalize(_d2DRenderer, m_managerSet, this);
	}

	// 시작씬을 지정한다.
	m_currentScene = m_sceneCotainer.find(_startScene)->second;

	m_currentScene->Enter();
	m_currentScene->Start();
}

void SceneManager::ChangeScene(const wstring& _sceneName)
{
	// 게임 종료
	if (_sceneName == L"ExitGame")
	{
		m_gameRun = false;
		return;
	}

	// 가지고 있는 씬인지 확인한다.
	auto iter = m_sceneCotainer.find(_sceneName);	
	
	assert(iter != m_sceneCotainer.end() || !L"변경하려는 씬이 없습니다");

	// 씬변경시 예외처리
	m_currentScene->Exit();
	m_isPause = false;
	m_collisionManager->Clear();
	m_managerSet->GetUIManager()->SetFocusedUI(nullptr);
	m_managerSet->GetCameraManager()->ResetCamera();
	m_directManager->Reset();
	NamingManager::GetInstance()->ClearNameInfo();

	// 다음씬 지정
	m_currentScene = iter->second;
	
	m_currentScene->AddMouse();
	m_currentScene->Enter();
	m_currentScene->Start();
}

void SceneManager::Finalize()
{
	for (auto& iter : m_sceneCotainer)
	{
		Scene* scene = iter.second;
		if (scene != nullptr)
		{
			scene->Finalize();
			delete scene;
		}
	}

	m_sceneCotainer.clear();
}
 
void SceneManager::RegisterNextScene(const wstring& _sceneName) const
{
	m_currentScene->RegisterNextScene(_sceneName);
}

void SceneManager::RegisterObject(GameObject* _object, float _delayTime /*=0.f*/) const
{
	m_currentScene->RegisterObject(_object, _delayTime);
}

void SceneManager::Update(float _deltaTime)
{
	m_currentScene->Update(_deltaTime);
}

void SceneManager::FixedUpdate(float _fiexedDeltaTime)
{
	m_currentScene->FixedUpdate(_fiexedDeltaTime);
}

void SceneManager::LateUpdate(float _deltaTime)
{
	m_currentScene->LateUpdate(_deltaTime);
}

void SceneManager::Render(D2DRenderer* _d2DRenderer)
{
	m_currentScene->Render(_d2DRenderer);
}

void SceneManager::DebugRender(D2DRenderer* _d2DRenderer)
{
	m_currentScene->DubugRender(_d2DRenderer);
}

void SceneManager::ProcessEvent(float _deltaTime)
{
	m_currentScene->ProcessEvent(_deltaTime);
}