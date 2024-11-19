#include "pch.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "TimeManager.h"

CameraManager::CameraManager(InputManager* inputManager)
	:m_moveSpeed(0.f), m_position(0.f, 0.f), m_inputManager(inputManager)
{
	m_moveSpeed = 600.f;
	m_scale ={ 1.f,1.f };
}

CameraManager::~CameraManager()
{

}

void CameraManager::Update(double deltatime)
{
	if (m_inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
	{
		m_scale.x += 0.1f;
		m_scale.y += 0.1f;
	} 
	if (m_inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
	{
		m_scale.x -= 0.1f;
		m_scale.y -= 0.1f;
	}

	if (m_inputManager->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD))
	{
		m_position.x -= m_moveSpeed *(deltatime);
	}
	if (m_inputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD))
	{
		m_position.x += m_moveSpeed * (deltatime);
	}
	if (m_inputManager->IsKeyState(KEY::UP, KEY_STATE::HOLD))
	{
		m_position.y += m_moveSpeed * (deltatime);
	}
	if (m_inputManager->IsKeyState(KEY::DOWN, KEY_STATE::HOLD))
	{
		m_position.y -= m_moveSpeed * (deltatime);
	}
} 
