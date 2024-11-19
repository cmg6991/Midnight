#include "GameProcessPCH.h"
#include "FadeOut.h"
#include "CameraManager.h"


FadeOut::FadeOut(bool _affectUI, const CameraManager* _cameraManager)
	:CameraEffect(CAMERA_EFFECT_TYPE::FADE_OUT, _affectUI,_cameraManager)
	, m_veilColor(ColorF::Black), m_alpha(0.f)
{

}

FadeOut::~FadeOut()
{

}


void FadeOut::Update(float _deltaTime)
{
	// 시간에 경과에 따라서 투명도가 증가한다. 
	float elasepTime = GetElaspedTime();
	
	float duration = GetDuration();

	elasepTime = FMath::Clamp(elasepTime + _deltaTime, 0.f, duration);
	
	// 알파값은 최대가 1.f 이다.
	m_alpha = elasepTime / duration;
	
	m_veilColor.a = m_alpha;

	SetElaspedTime(elasepTime);
	
	if (elasepTime == duration)
	{
		SetFinish(true);
	}
}

void FadeOut::Render(D2DRenderer* _d2DRenderer)
{
	const CameraManager* cameraMgr = GetCameraManager();
	Vector2 screenSize = cameraMgr->GetScreenSize();

	_d2DRenderer->DrawFillRectangle(Vector2::Zero, screenSize, m_veilColor);
}



