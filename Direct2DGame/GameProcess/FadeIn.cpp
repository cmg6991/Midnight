#include "GameProcessPCH.h"
#include "FadeIn.h"
#include "CameraManager.h"

FadeIn::FadeIn(bool _affectUI, const CameraManager* _cameraManager)
	:CameraEffect(CAMERA_EFFECT_TYPE::FADE_IN, _affectUI,_cameraManager)
	,m_veilColor(ColorF::Black), m_alpha(1.f)
{

}

FadeIn::~FadeIn()
{

}

void FadeIn::Render(D2DRenderer* _d2DRenderer)
{
	const CameraManager* cameraMgr = GetCameraManager();
	Vector2 screenSize = cameraMgr->GetScreenSize();

	_d2DRenderer->DrawFillRectangle(Vector2::Zero, screenSize, m_veilColor);
}

void FadeIn::Update(float _deltaTime)
{
	// 시간에 경과에 따라서 투명도가 증가한다. 
	float elasepTime = GetElaspedTime();

	float duration = GetDuration();

	elasepTime = FMath::Clamp(elasepTime + _deltaTime, 0.f, duration);

	m_alpha = 1.f - (elasepTime / duration);

	m_veilColor.a = m_alpha;

	SetElaspedTime(elasepTime);

	if (elasepTime == duration)
	{
		SetFinish(true);
	}
}
