#pragma once

#include "CameraEffect.h"

/// <summary>
/// 래터박스 효과
/// </summary>
class Letterbox :
    public CameraEffect
{
public:
    Letterbox(bool _affectUI, const CameraManager* _cameraManager);
    ~Letterbox();

public:
	void Render(D2DRenderer* _d2DRenderer) override;
	void Update(float _deltaTime) override;
	void Close() { m_isDone = true; }
	void SetUp(float _maxHeight, float _speed, Vector2 _screenSize);
private:
	float m_isDone; // 레터박스 효과가 끝났는지
	float m_maxHeight; // 레터박스 최대 높이
	float m_currentHeight; // 레터박스 현재높이 
	float m_speed; // 레터박스 올라가는 속도
	Vector2 m_screenSize;
};

