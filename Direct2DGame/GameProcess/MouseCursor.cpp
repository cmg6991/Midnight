#include "GameProcessPCH.h"
#include "MouseCursor.h"
#include "ManagerSet.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"

MouseCursor::MouseCursor()
	: MonoBehaviour(typeid(this).name())
	, m_inputManager(nullptr), m_isActive(false)
{
}

MouseCursor::~MouseCursor()
{

}

void MouseCursor::Start()
{
	m_inputManager = GetManagerSet()->GetInputManager();
	if (GetSceneManager()->GetCurrentScene()->GetSceneName() == L"MainScene"
		|| GetSceneManager()->GetCurrentScene()->GetSceneName() == L"CrewScene")
	{
		m_isActive = true;
	}
}

void MouseCursor::Update(float _dt)
{
	
}

void MouseCursor::Render(D2DRenderer* _d2DRenderer)
{
	if (m_isActive)
	{
		Vector2 position = m_inputManager->GetWorldMousePosition() + Vector2(16, -16);
		_d2DRenderer->DrawBitmap(L"mouse", position);
	}
}

Component* MouseCursor::Clone()
{
	return nullptr;
}
