#include "GameProcessPCH.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	:m_curentCount{}
	,m_frequency{}
	,m_prevCount{}
	,m_deltaTime(0.)
	,m_elapsedTime(0.)
	,m_fps(0)
	,m_updateCount(0)
	,m_screenSize{}
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Initalize(const Vector2& _screenSize)
{
	QueryPerformanceFrequency(&m_frequency); // 프로세서의 카운터 값의 빈도
	QueryPerformanceCounter(&m_prevCount); // 이전 프레임의 카운터 값 
	QueryPerformanceCounter(&m_curentCount);
	m_screenSize = _screenSize;
}

double TimeManager::Update()
{
	QueryPerformanceCounter(&m_curentCount);

	m_deltaTime = (m_curentCount.QuadPart - m_prevCount.QuadPart) / (double)m_frequency.QuadPart;

	m_prevCount = m_curentCount;

	++m_updateCount;
	m_elapsedTime += m_deltaTime;
	if (m_elapsedTime >= 1.)
	{
		m_elapsedTime -= 1.;
		m_fps = m_updateCount;
		m_updateCount = 0;
	}


	//if (m_deltaTime >= 0.02f)
	//{
	//	m_deltaTime = 0.02f;
	//}

	return m_deltaTime;
}

void TimeManager::DebugRender(D2DRenderer* _d2dRenderer)
{
	wstring str = L"FPS : " + std::to_wstring(m_fps) + L" DT : " + std::to_wstring(m_deltaTime);
	Vector2 leftTop{ -m_screenSize.x * 0.5f, m_screenSize.y * 0.5f }, rightBottom{ 0.f,0.f };

	_d2dRenderer->SetCameraAffected(false);
	_d2dRenderer->DrawTextW(str, leftTop, rightBottom, D2D1::ColorF::Gold);
}

void TimeManager::Finalize()
{
}
