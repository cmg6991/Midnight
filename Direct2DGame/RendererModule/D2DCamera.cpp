#include "RendererPCH.h"
#include "D2DCamera.h"

D2DCamera::D2DCamera()
	:m_cameraMatrix{}
	,m_position{0.f,0.f}
	,m_rotation(0.f)
	,m_scale{1.f,1.f}
{}

D2DCamera::~D2DCamera()
{}

void D2DCamera::RotateCamera(float _radian)
{
	// 스크린 좌표계로 변환
	m_rotation -= _radian;
	CalculateMatrix();
}

void D2DCamera::MoveCamera(Vector2 _distance)
{
	// 스크린 좌표계로 변환
	m_position -= _distance.ChangeYSign();
	CalculateMatrix();
}

void D2DCamera::SetPosition(Vector2 _position)
{
	m_position = Vector2(_position.x * -1.f, _position.y);
	CalculateMatrix();
}

Vector2 D2DCamera::GetPosition()
{
	Vector2 position{ -m_position.x, m_position.y };
	return position;
}

void D2DCamera::ZoomCamera(Vector2 _scale)
{
	m_scale += _scale;
		
	constexpr float Min = 0.5f;
	constexpr float Max = 1.f;

	m_scale.x = FMath::Clamp(m_scale.x, Min, Max);
	m_scale.y = FMath::Clamp(m_scale.y, Min, Max);

	CalculateMatrix();
}

void D2DCamera::ResetCamera(Vector2 _screenSize)
{
	m_rotation = 0.f;
	m_position = Vector2(0.f, 0.f);
	m_scale = Vector2(1.f, 1.f);
	m_screenSize = _screenSize;

	m_cameraMatrix = D2D1::Matrix3x2F::Identity();
}

Vector2 D2DCamera::ScreenToWorld(const Vector2& _screen)
{
	Vector2 camera = ScreenToCamera(_screen);

	return CameraToWorld(camera);
}

Vector2 D2DCamera::ScreenToCamera(const Vector2& _screen)
{
	// y좌표 반대, 중심점 좌표 이동
	Vector2 camera{};
	camera.x = _screen.x  - m_screenSize.x *0.5f;
	camera.y = -_screen.y + m_screenSize.y * 0.5f; 

	return camera;
}


Vector2 D2DCamera::CameraToScreen(const Vector2& _camera)
{
	Vector2 screen{};
	 
	screen.x = _camera.x + m_screenSize.x *0.5f;
	screen.y = -_camera.y + m_screenSize.y * 0.5f;

	return screen;
}

Vector2 D2DCamera::CameraToWorld(const Vector2& _camera)
{
	Vector2 world{};

	// 스케일
	world.x = _camera.x / m_scale.x;
	world.y = _camera.y / m_scale.y;
	
	// 회전
	world = Vector2::RotateRadian(world, Vector2::Zero, m_rotation);

	// 이동
	// 카메라 반대방향은 빼줘야하고 y좌표는 부호가 반대이므로 아래과 같은 식이 나온다
	world.x -= m_position.x;
	world.y += m_position.y;

	return world;
}


Vector2 D2DCamera::WorldToCamera(const Vector2& _world)
{
	Vector2 camera{};

	// 크기
	camera.x = _world.x * m_scale.x;
	camera.y = _world.y * m_scale.y;

	// 회전
	camera = Vector2::RotateRadian(camera, Vector2::Zero, -m_rotation);

	// 이동
	camera.x = camera.x + m_position.x;
	camera.y = camera.y - m_position.y;
		
	return camera;
}


Vector2 D2DCamera::WorldtoScreen(const Vector2& _world)
{
	Vector2 camera = WorldToCamera(_world);

	return CameraToScreen(camera);
}

void D2DCamera::CalculateMatrix()
{
	float angle = FMath::RadToDeg(m_rotation);
	D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(angle);
	D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(m_scale.x, m_scale.y);
	D2D1_MATRIX_3X2_F position = D2D1::Matrix3x2F::Translation(m_position.x, m_position.y);

	// 최종 변환 행렬         
	m_cameraMatrix = position * rotation * scale;
}
