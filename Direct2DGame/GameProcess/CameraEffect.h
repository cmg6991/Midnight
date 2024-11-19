#pragma once

class CameraManager;

/// <summary>
///  카메라 이펙트의 추상클래스 
/// 
/// 2023.7.27 12:03 gitae
/// </summary>
class CameraEffect
{
public:
	CameraEffect(CAMERA_EFFECT_TYPE _type, bool _isAffectUI,const CameraManager* _cameraManager);
	~CameraEffect();

	float GetDuration() const { return m_duration; }
	void SetDuration(float val) { m_duration = val; }

	bool IsAffectUI() { return m_isAffectUI; }

	float GetElaspedTime() const { return m_elaspedTime; }
	void SetElaspedTime(float val) { m_elaspedTime = val; }
	const CameraManager* GetCameraManager() const { return m_cameraManager; }
	void SetCameraManager(CameraManager* val) { m_cameraManager = val; }
	bool IsFinish() const { return m_isFinish; }
	void SetFinish(bool val) { m_isFinish = val; }
public:
	virtual void Render(D2DRenderer* _d2DRenderer) abstract;
	virtual void Update(float _deltaTime) abstract;
	CAMERA_EFFECT_TYPE GetEffectType() { return m_type; }

private:
	const CameraManager* m_cameraManager;
	CAMERA_EFFECT_TYPE m_type; // 카메라 효과
	bool m_isAffectUI; // UI에도 영향을 미치는 카메라 효과인지
	float m_duration; 
	float m_elaspedTime; 
	bool m_isFinish; // 끝난 이펙트인지

};

