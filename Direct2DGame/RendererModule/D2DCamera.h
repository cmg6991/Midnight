#pragma once

// 2023.7.5 21:58 gitae
// D2D에서 카메라를 담당한다.
class D2DCamera
{
public:
	D2DCamera();
	~D2DCamera();
	// 카메라 회전
	void RotateCamera(float _radian);
	
	// 카메라 이동
	void MoveCamera(Vector2 _distance);

	void SetPosition(Vector2 _position);
	
	// 카메라 확대 축소
	void ZoomCamera(Vector2 _scale);

	// 카메라를 기본 행렬로 초기화한다. 
	void ResetCamera(Vector2 _screenSize);

	const D2D1_MATRIX_3X2_F& GetCameraMatrix() { return m_cameraMatrix; }

	Vector2 GetPosition();
	const Vector2& GetScale() { return m_scale; }
	float GetRotation() { return m_rotation; }
	
	
public:
	Vector2 CameraToWorld(const Vector2& _camera);
	Vector2 CameraToScreen(const Vector2& _camera);
	Vector2 WorldToCamera(const Vector2& _world);
	Vector2 WorldtoScreen(const Vector2& _world);
	Vector2 ScreenToWorld(const Vector2& _screen);
	Vector2 ScreenToCamera(const Vector2& _screen);

private:
	void CalculateMatrix();

private:
	float m_rotation; // 카메라 회전
	Vector2 m_scale; // 카메라 배율
	Vector2 m_position; // 카메라 좌표

	Vector2 m_screenSize; // 스크린 사이즈

	D2D1_MATRIX_3X2_F m_cameraMatrix;
};

