#pragma once
#include "MonoBehaviour.h"

class ThreadMove : public MonoBehaviour
{
public:
	ThreadMove();
	~ThreadMove();

	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;
	/// 가장 기본적인 랜더링 이벤트
	void Render(D2DRenderer* _d2DRenderer) override;

	void PostRender(D2DRenderer* _d2DRenderer) override;
	/// 디버그 전용 랜더링 함수 F5를 온오프
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnCollisionExit(const Collision& _collision) override;
private:

	Transform* m_transform;
	RigidBody* m_rigidBody;

	Vector2 m_position;
	Vector2 m_prePosition;
	bool m_isThreadDestroy;
	bool m_isSoundStop;
};

