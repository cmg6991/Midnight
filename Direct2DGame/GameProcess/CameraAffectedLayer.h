#pragma once
class D2DCamera;
class Transform;


/// <summary>
/// 
/// 2023 08 12 손서희
/// </summary>

///카메라(시점)의 영향을 받아 위치값을 수정해주는 컴포넌트
#include "Component.h"
class CameraAffectedLayer : public Component
{
/// 생성자와 소멸자  ===================================================================
public:
	CameraAffectedLayer();
	~CameraAffectedLayer();

	Component* Clone() override;

	void Start() override;

///맴버 함수  =========================================================================
public:
	void Update(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer) override;
	void DebugRender(D2DRenderer* _d2DRendere) override;

	void SetDepth(float _depth) { m_depth = _depth; }
	float getDepth() { return m_depth; }


///맴버 변수  =========================================================================
private:
	D2DCamera* m_camera;
	const CameraManager* m_cameraManager;
	Transform* m_transform;
	float m_depth; //카메라에 영향을 받는 정도 ( 0 : 영향을 받지 않음, 1 : 카메라랑 같이 움직임)

	bool m_isReady;
	float m_timer;
};

