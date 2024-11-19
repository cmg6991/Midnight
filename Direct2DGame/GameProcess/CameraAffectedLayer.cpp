#include "GameProcessPCH.h"
#include "CameraAffectedLayer.h"
#include "ManagerSet.h"
#include "CameraManager.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "D2DCamera.h"

CameraAffectedLayer::CameraAffectedLayer()
	: Component(CALL_ORDER::CAMERA_AFFECTED_LAYER, typeid(this).name())
	, m_camera(nullptr), m_transform(nullptr), m_cameraManager(nullptr)
	, m_depth(0), m_isReady(false), m_timer(0.f)
{
}

CameraAffectedLayer::~CameraAffectedLayer()
{

}

Component* CameraAffectedLayer::Clone()
{
	CameraAffectedLayer* clone = new CameraAffectedLayer();
	clone->m_depth = this->m_depth;

	return clone;
}

void CameraAffectedLayer::Start()
{
	m_transform = GetComponent<Transform>();
	m_cameraManager = GetManagerSet()->GetCameraManager();
	m_camera = GetManagerSet()->GetCameraManager()->GetCamera();
}

void CameraAffectedLayer::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (m_timer > 0.1f) m_isReady = true;

	if (m_isReady)
	{
		Vector2 pos = m_transform->GetPosition();
		Vector2 dxdy = m_cameraManager->GetDxdy();

		m_transform->SetPosition(pos + dxdy * m_depth);
	}
}

void CameraAffectedLayer::Render(D2DRenderer* _d2DRenderer)
{

}

void CameraAffectedLayer::DebugRender(D2DRenderer* _d2DRendere)
{

}
