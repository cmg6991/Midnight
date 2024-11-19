#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	:m_currentCount{}
	, m_frequency{}
	, m_prevCount{}
	, m_deltaTime(0.)
{

}

TimeManager::~TimeManager()
{

}
	
void TimeManager::Initalize()
{
	// 1초에 만번정도 카운트를 함 아마
	QueryPerformanceFrequency(&m_frequency); // 프로세서의 카운터 값의 빈도

	//현재카운트를 받아옴
	QueryPerformanceCounter(&m_prevCount); // 이전 프레임의 카운터 값
}

double TimeManager::Update()
{
	QueryPerformanceCounter(&m_currentCount);
	m_deltaTime = (m_currentCount.QuadPart - m_prevCount.QuadPart) / (double)m_frequency.QuadPart;

	m_prevCount = m_currentCount;

	//// TimeManager
	//static double elapsedTime = 0.;
	//elapsedTime += m_deltaTime;
	//static int fpsCount = 0;
	//fpsCount++; 

	//if (elapsedTime >= 1.)
	//{
	//fpsCount->
	//}

	return m_deltaTime;
}