#include "GameProcessPCH.h"
#include "Letterbox.h"


Letterbox::Letterbox(bool _affectUI, const CameraManager* _cameraManager)
	:CameraEffect(CAMERA_EFFECT_TYPE::LETTERBOX,_affectUI,_cameraManager)
	,m_maxHeight(0.f)
	,m_currentHeight(0.f)
	,m_speed(0.f)
	,m_isDone(false)
	,m_screenSize(Vector2::Zero)
{
}

Letterbox::~Letterbox()
{

}

void Letterbox::Render(D2DRenderer* _d2DRenderer)
{
	// 상단 레터박스
	Vector2 leftTop1{ -m_screenSize.x * 0.5f , m_screenSize.y * 0.5f };
	Vector2 rightBottom1{ m_screenSize.x * 0.5f, m_screenSize.y * 0.5f - m_currentHeight };

	_d2DRenderer->DrawFillRectangle2(leftTop1, rightBottom1, ColorF(ColorF::Black));

	//하단 레터박스 

	Vector2 leftTop2{ -m_screenSize.x * 0.5f , -m_screenSize.y * 0.5f };
	Vector2 rightBottom2{ m_screenSize.x * 0.5f, -m_screenSize.y * 0.5f + m_currentHeight };

	_d2DRenderer->DrawFillRectangle2(leftTop2, rightBottom2, ColorF(ColorF::Black));
}

void Letterbox::Update(float _deltaTime)
{
	if (m_isDone)
	{
		m_currentHeight -= m_speed * _deltaTime;
	}
	else
	{
		m_currentHeight += m_speed * _deltaTime;
	}

	m_currentHeight = FMath::Clamp(m_currentHeight, 0.f, m_maxHeight);

	if (m_isDone && m_currentHeight == 0.f)
	{
		SetFinish(true);
		SetElaspedTime(GetDuration());
	}

}

void Letterbox::SetUp(float _maxHeight, float _speed, Vector2 _screenSize)
{
	m_maxHeight = _maxHeight;
	m_speed = _speed;
	m_screenSize = _screenSize;

}
