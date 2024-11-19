#include "GameProcessPCH.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "CameraEffect.h"
#include "FadeOut.h"
#include "FadeIn.h"
#include "GameObject.h"
#include "Letterbox.h"
#include "Transform.h"

CameraManager::CameraManager()
	:m_camera(nullptr)
	, m_d2DRenderer(nullptr)
	, dist(0.f)
	, m_screenSize{}
	, m_inputManager(nullptr)
	, m_moveSpeed(0.f)
	, m_effectList{}
	, m_targetObject(nullptr)
	, m_trackingSpeed(0.f)
	, m_prevDistance(0.f)
	, m_mode(CAMERA_MODE::MIDNIGHT), m_isTracking(false)
	, m_offset(Vector2(0.f, 0.f)), m_currentOffset(m_offset)
	, m_isChangingOffset(false)
	, m_dxdy(Vector2(0, 0)), m_prevPosition(Vector2(0, 0))
	, m_topBorder(2160 - 400), m_bottomBorder(-100 + 400), m_rightBorder(1500 - 500), m_leftBorder(-1500 + 500)
	, m_topTouch(false)
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::Initalize(D2DRenderer* _renderer, Vector2 _screenSize, InputManager* _inputManager)
{
	m_screenSize = _screenSize;
	m_d2DRenderer = _renderer;
	m_camera = m_d2DRenderer->GetCamera();
	m_inputManager = _inputManager;

	m_moveSpeed = 300.f;
	m_trackingSpeed = 200.f;

	m_prevPosition = m_camera->GetPosition();
	m_camera->SetPosition(Vector2(0.f, m_bottomBorder));
}

void CameraManager::Update(float _deltaTime)
{
	/// 카메라 위치 변화량 업데이트
	Vector2 curPos = m_camera->GetPosition();
	m_dxdy = curPos - m_prevPosition;
	m_prevPosition = curPos;

	/// 카메라 이동 관련
	switch (m_mode)
	{
	case CAMERA_MODE::DEFAULT:
	
		break;

	case CAMERA_MODE::MIDNIGHT:
		MidnightMove(_deltaTime);
		break;

	case CAMERA_MODE::MOUSE:
		TargetTracking(_deltaTime);
		break;

	case CAMERA_MODE::MAINSCENE:
		MainSceneMode(_deltaTime);
		break;
	}


	/// 카메라 효과 관련 
	if (!m_effectList.empty())
	{
		CameraEffect* effect = m_effectList.front().get();
		effect->Update(_deltaTime);

		if (effect->GetDuration() == effect->GetElaspedTime())
		{
			m_effectList.pop_front();
		}
	}

}

void CameraManager::Render(D2DRenderer* _d2DRenderer)
{
	_d2DRenderer->SetCameraAffected(false);
	if (!m_effectList.empty())
	{
		m_effectList.front()->Render(_d2DRenderer);
	}
}

void CameraManager::DebugRender(D2DRenderer* _d2DRenderer)
{
	//카메라 포지션 출력
	_d2DRenderer->SetCameraAffected(true);
	Vector2 cameraPos = m_camera->GetPosition();
	_d2DRenderer->DrawFillElipse(cameraPos, Vector2(10, 10), D2D1::ColorF::Red);

	//디버그 정보 출력
	_d2DRenderer->SetCameraAffected(false);
	wstring str = L"카메라 좌표 X: " + std::to_wstring(cameraPos.x) + L" Y: " + std::to_wstring(cameraPos.y);
	Vector2 leftTop{ -m_screenSize.x * 0.5f, m_screenSize.y * 0.5f - 20.f }, rightBottom{ 0.f,0.f };
	_d2DRenderer->DrawTextW(str, leftTop, rightBottom, D2D1::ColorF::Gold);

	str = L"distance : " + std::to_wstring(dist);
	_d2DRenderer->DrawTextW(str, leftTop + Vector2(0, -15), rightBottom + Vector2(0, -15), D2D1::ColorF::Gold);

	str = L"cur offset : " + std::to_wstring(m_currentOffset.y);
	_d2DRenderer->DrawTextW(str, leftTop + Vector2(0, -30), rightBottom + Vector2(0, -30), D2D1::ColorF::Gold);

	str = L"offset : " + std::to_wstring(m_offset.y);
	_d2DRenderer->DrawTextW(str, leftTop + Vector2(0, -45), rightBottom + Vector2(0, -45), D2D1::ColorF::Gold);

	_d2DRenderer->SetCameraAffected(true);
	//카메라 보더 출력
	_d2DRenderer->DrawRectangle(Vector2(m_leftBorder, m_topBorder), Vector2(m_rightBorder, m_bottomBorder), D2D1::ColorF::Azure);



	_d2DRenderer->SetCameraAffected(true);
}

void CameraManager::SetTargetObject(GameObject* _target) const
{
	if (_target == nullptr)
	{
		m_targetObject = nullptr;
	}
	else if (_target->IsAlive())
	{
		m_targetObject = _target;
		m_targetTransform = m_targetObject->GetComponent<Transform>();
	}
}

Vector2 CameraManager::ScreenToWorld(const Vector2& _screen) const
{
	Vector2 camera = m_camera->ScreenToCamera(_screen);
	return m_camera->CameraToWorld(camera);
}

Vector2 CameraManager::ScreenToCamera(const Vector2& _screen) const
{
	return m_camera->ScreenToCamera(_screen);
}

Vector2 CameraManager::WorldToCamera(const Vector2& _world) const
{
	return m_camera->WorldToCamera(_world);
}

Vector2 CameraManager::WorldToScreen(const Vector2& _world) const
{
	Vector2 camera = m_camera->WorldToCamera(_world);

	return m_camera->CameraToScreen(camera);
}

Vector2 CameraManager::CameraToScreen(const Vector2& _camera) const
{
	return m_camera->CameraToScreen(_camera);
}

Vector2 CameraManager::CameraToWorld(const Vector2& _camera) const
{
	return m_camera->CameraToWorld(_camera);
}

void CameraManager::ResetCamera() const
{
	m_camera->ResetCamera(m_screenSize);
	m_offset = Vector2::Zero;
	SetTargetObject(nullptr);
	m_effectList.clear();
}

void CameraManager::SetCameraBorder(float _top, float _bottom, float _left, float _right) const
{
	m_leftBorder = _left;
	m_rightBorder = _right;
	m_topBorder = _top;
	m_bottomBorder = _bottom;
}

void CameraManager::SetCameraPos(Vector2 _pos) const
{
	m_camera->SetPosition(_pos);
}

void CameraManager::FadeInCamera(float _duration, bool _isAffectUI, ColorF color /*= ColorF::Black*/) const
{
	std::unique_ptr<CameraEffect> effect(new FadeIn(_isAffectUI, this));

	effect->SetDuration(_duration);
	FadeIn* fadein = dynamic_cast<FadeIn*>(effect.get());
	fadein->SetVeilColor(color);

	m_effectList.push_back(std::move(effect));
}

void CameraManager::FadeOutCamera(float _duration, bool _isAffectUI, ColorF color /*= ColorF::Black*/) const
{
	std::unique_ptr<CameraEffect> effect(new FadeOut(_isAffectUI, this));

	effect->SetDuration(_duration);
	FadeOut* fadeout = dynamic_cast<FadeOut*>(effect.get());
	fadeout->SetVeilColor(color);

	m_effectList.push_back(std::move(effect));
}


void CameraManager::LetterboxCamera(float _heigt, float _speed) const
{
	std::unique_ptr<CameraEffect> effect(new Letterbox(false, this));

	Letterbox* letterbox = dynamic_cast<Letterbox*>(effect.get());
	letterbox->SetUp(_heigt, _speed, m_screenSize);
	letterbox->SetDuration(1.f);

	m_effectList.push_back(std::move(effect));
}

void CameraManager::ClearCameraEffect()const
{
	m_effectList.clear();
}

void CameraManager::MouseToCameraMove(float _deltaTime)
{
	///// 1. 맵사이즈 제한해서 카메라 움직이기
	///// 2. 특정영역에 마우스가 있으면 카메라 움직이기 
	Vector2 mouseScreenPos = m_inputManager->GetScreendMousePosition();

	Vector2 direction = Vector2::Zero;
	// 상단 이동
	if (mouseScreenPos.y <= 50.f)
	{
		++direction.y;
	}
	// 하단 이동
	if (mouseScreenPos.y >= m_screenSize.y - 50.f)
	{
		--direction.y;
	}
	// 좌 이동
	if (mouseScreenPos.x <= 50.f)
	{
		--direction.x;
	}
	// 우 이동
	if (mouseScreenPos.x >= m_screenSize.x - 50.f)
	{
		++direction.x;
	}

	direction.Normalize();

	Vector2 distance = direction * m_moveSpeed * _deltaTime;

	m_camera->MoveCamera(distance);

	if (m_inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
	{
		m_camera->ZoomCamera(Vector2(0.1f, 0.1f));
	}
	if (m_inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
	{
		m_camera->ZoomCamera(Vector2(-0.1f, -0.1f));
	}
}

void CameraManager::TargetTracking(float _deltaTime)
{
	// 삭제 예외처리
	if (!m_targetObject->IsAlive())
	{
		m_targetObject = nullptr;
	}

	Vector2 targetPosition = m_targetObject->GetComponent<Transform>()->GetPosition();
	Vector2 cameraPos = m_camera->GetPosition();

	float distance = (cameraPos -targetPosition).Length();

	if(distance >= 10.f)
	{
		Vector2 direct = (cameraPos - targetPosition).GetNormalize();
		Vector2 moveDistance = direct * m_trackingSpeed * _deltaTime;

		// 이동거리 
		m_camera->SetPosition(cameraPos - moveDistance);
	}

}

void CameraManager::MidnightMove(float _deltaTime)
{
	if (!m_targetObject)
		return;

	// 삭제 예외처리
	if (!m_targetObject->IsAlive())
	{
		m_targetObject = nullptr;
	}

	//위치
	Vector2 targetPos = m_targetTransform->GetPosition();
	Vector2 cameraPos = m_camera->GetPosition();


	dist = Vector2::Distance(targetPos, cameraPos);

	//추적여부 계산
	if (m_HeightBorder < abs(targetPos.y - cameraPos.y)
		|| m_widthBorder < abs(targetPos.x - cameraPos.x))
		m_isTracking = true;

	else if (dist < 10.f /* && !m_isChangingOffset*/)	///오프셋이 남아있는 문제가 있다.
		m_isTracking = false;

	///1안 : 남은 거리에 따른 비율 곱해주기
	float speedRatio = 1.f;
	if (m_topBorder < targetPos.y)	speedRatio = speedRatio + (targetPos.y - m_topBorder) / 250.f;
	if (targetPos.y < m_bottomBorder) speedRatio = speedRatio + abs(targetPos.y - m_bottomBorder) / 250.f;
	
	
	if (m_topBorder < targetPos.y)	targetPos.y = m_topBorder;
 	if (targetPos.y < m_bottomBorder) targetPos.y = m_bottomBorder;

	if (m_rightBorder < targetPos.x) targetPos.x = m_rightBorder;
	if (targetPos.x < m_leftBorder)	 targetPos.x = m_leftBorder;

	//추적
	if (m_isTracking == true)
	{
// 		float ratio = _deltaTime * m_speed;
// 		float distance = (cameraPos - targetPos).Length();
// 		if (distance >= 300.f)
// 		{
// 			ratio *= 1.5f;
// 		}

		//cameraPos = Vector2::Lerp(cameraPos, targetPos, ratio);
		cameraPos = Vector2::Lerp(cameraPos, targetPos, _deltaTime * m_speed * 1.5f * speedRatio);
	}

	///2안 냅다 박아버리기
// 	if (m_topBorder < cameraPos.y)	cameraPos.y = m_topBorder;
// 	if (cameraPos.y < m_bottomBorder) cameraPos.y = m_bottomBorder;


	m_camera->SetPosition(cameraPos);
	//m_camera->SetPosition(targetPos);
}

void CameraManager::MainSceneMode(float _dt)
{
	if (m_targetObject != nullptr)
	{
		Vector2 pos = m_targetTransform->GetPosition() + m_offset;
		m_camera->SetPosition(pos);
	}
}

void CameraManager::SetGravityMode(int _i) const
{
	if (_i == -1) //inverse
		m_offset.y = abs(m_offset.y) * -1;

	else
		m_offset.y = abs(m_offset.y);

	m_isChangingOffset = true;

}