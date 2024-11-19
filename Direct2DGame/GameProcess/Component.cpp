#include "GameProcessPCH.h"
#include "Component.h"
#include "GameObject.h"


Component::Component(CALL_ORDER _callOrder, string _name)
	:m_name(_name)
	,m_callOrder(_callOrder)
	,m_gameObject(nullptr)
{


}


Component::Component()
	:m_name()
	,m_callOrder(CALL_ORDER::MONO_BEHAVIOUR)
	,m_gameObject(nullptr)

{

}

Component::~Component()
{

}

const ManagerSet* Component::GetManagerSet() const
{
	return m_gameObject->GetManagerSet();
}

const CameraManager* Component::GetCameraManager() const
{
	return m_gameObject->GetCameraManager();
}

const PathManager* Component::GetPathManager() const
{
	return m_gameObject->GetPathManager();
}

const InputManager* Component::GetInputManager() const
{
	return m_gameObject->GetInputManager();
}

const TimeManager* Component::GetTimeManager() const
{
	return m_gameObject->GetTimeManager();
}

const SceneManager* Component::GetSceneManager() const
{
	return m_gameObject->GetSceneManager();
}

const UIManager* Component::GetUIManager() const
{
	return m_gameObject->GetUIManager();
}

const CollisionManager* Component::GetCollisionManager() const
{
	return m_gameObject->GetCollisionManager();
}

const DirectManager* Component::GetDirectManager() const
{
	return m_gameObject->GetDirectManager();
}

const PhysicsManager* Component::GetPhysicsManager() const
{
	return m_gameObject->GetPhysicsManager();
}
