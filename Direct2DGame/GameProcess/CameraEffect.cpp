#include "GameProcessPCH.h"
#include "CameraEffect.h"


CameraEffect::CameraEffect(CAMERA_EFFECT_TYPE _type, bool _isAffectUI, const CameraManager* _cameraManager)
	:m_isAffectUI(_isAffectUI), m_type(_type)
	, m_elaspedTime(0.f), m_duration(0.f)
	,m_cameraManager(_cameraManager)
	,m_isFinish(false)
{

}

CameraEffect::~CameraEffect()
{

}

