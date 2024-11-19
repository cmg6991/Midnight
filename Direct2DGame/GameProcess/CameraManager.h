#pragma once

class InputManager;
class CameraEffect;
class Transform;

enum class CAMERA_MODE
{
	DEFAULT,
	MIDNIGHT,
	MOUSE,
	MAINSCENE,
};


/// <summary>
/// 카메라를 담당하는 매니져
/// 
/// 2023.07.07 23:04 gitae
/// 2023.08.10 서희
/// </summary>
class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void Initalize(D2DRenderer* _renderer, Vector2 _screenSize, InputManager* _inputManager);
	void Update(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2DRenderer);


public:
	void SetTargetObject(GameObject* _target) const;

	/// 스크린 좌표계에서 월드 좌표계로 변환해준다.
	Vector2 ScreenToWorld(const Vector2& _screen) const;

	// 스크린 좌표계에서 카메라 좌표계로 변환
	Vector2 ScreenToCamera(const Vector2& _screen) const;
	
	// 월드좌표에서 카메라 좌표계로 변환
	Vector2 WorldToCamera(const Vector2& _world) const;
	
	// 월드 좌표에서 스크린 좌표계로 변환 
	Vector2 WorldToScreen(const Vector2& _world) const;
	
	// 카메라 좌표계에서 스크린 좌표계 변환
	Vector2 CameraToScreen(const Vector2& _camera) const;
	
	// 카메라 좌표계에서 월드 좌표계 변환 
	Vector2 CameraToWorld(const Vector2& _camera) const;
	
	void ResetCamera()const;

	Vector2 GetScreenSize()const { return m_screenSize; }
	
	void SetCameraMode(CAMERA_MODE _mode) const { m_mode = _mode; }
	void SetGravityMode(int _i) const;
	D2DCamera* GetCamera() const { return m_camera; } 
	Vector2 GetDxdy() const { return m_dxdy; }
	void SetCameraBorder(float _top, float _bottom, float _left, float _right) const;
	void SetCameraPos(Vector2 _pos = Vector2(0, 0)) const;
	CameraEffect* GetCurrentCameraEffect()const { return m_effectList.front().get(); }
	void SetOffset(Vector2 _offset) const { m_offset = _offset; }

public:
	/// 카메라 효과 목록 
	void FadeInCamera(float _duration, bool _isAffectUI,ColorF color = ColorF::Black) const;
	void FadeOutCamera(float _duration, bool _isAffectUI ,ColorF color = ColorF::Black) const;
	void LetterboxCamera(float _heigt, float _speed)const;
	void ClearCameraEffect()const;

private:
	void MouseToCameraMove(float _deltaTime);
	void TargetTracking(float _deltaTime);
	void MidnightMove(float _deltaTime);
	void MainSceneMode(float _dt);

private:
	D2DCamera* m_camera;
	D2DRenderer* m_d2DRenderer;
	Vector2 m_screenSize;
	InputManager* m_inputManager;
	
	float m_moveSpeed;// 카메라 이동속도
	float m_trackingSpeed; // 추적속도 
	Vector2 m_tarckDistance;
	float m_prevDistance; // 이전 거리 차이

	mutable GameObject* m_targetObject;
	mutable Transform* m_targetTransform;
	mutable list<std::unique_ptr<CameraEffect>> m_effectList;

	mutable CAMERA_MODE m_mode;

	//미드나잇 전용 변수 ---------------------------------
	bool m_isTracking;	
	const float m_speed = 2.f;
	const float m_HeightBorder = 80.f;
	const float m_widthBorder = 150.f;
	mutable Vector2 m_offset;
	Vector2 m_currentOffset;
	mutable bool m_isChangingOffset;

	mutable float m_topBorder;
	mutable float m_bottomBorder;
	mutable float m_leftBorder;
	mutable float m_rightBorder;

	bool m_topTouch;

	float dist; ///임시변수입니다용 디버깅끝나면 삭제할 예정!!!!

	//---------------------------------

	Vector2 m_dxdy;
	Vector2 m_prevPosition;
};

