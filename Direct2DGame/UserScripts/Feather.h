#pragma once
#include "MonoBehaviour.h"

class Feather : public MonoBehaviour
{
public:
	Feather();
	~Feather();
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

	void OnCollisionEnter(const Collision& _collision) override;

	void Wait();
	void Wait2Second();
	void MakeFeather();

private:
	RigidBody* m_rigidBody;
	TextureRenderer* m_textureRenderer;
	Transform* m_transform;
	ParticleSystem* m_particleSystem;

	Vector2 m_featherPosition;

	float m_waitTime;
	float m_deltaTime;
	float m_alpha;
	float m_wait2Second;

	bool m_isStepOn;
	bool m_isFadeOut;
	bool m_isRecreate;
};

