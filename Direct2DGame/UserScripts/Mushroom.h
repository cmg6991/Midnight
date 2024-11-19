#pragma once
#include "MonoBehaviour.h"

class Mushroom : public MonoBehaviour
{
public:
	Mushroom();
	~Mushroom();
	Component* Clone() override;

	void Start() override;
	void Update(float _deltaTime) override;
	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;

private:
	TextureRenderer* m_texture;
	BoxCollider* m_boxcollider;
	ParticleSystem* m_particleSystem;
	RigidBody* m_rigidBody;

	float m_BounceTimer;
	float m_BounceTime;
	bool m_touch;

	Vector2 m_originPos;
	Vector2 m_lowPos;
	float m_amplitute;

	float m_timer;
	float m_lastExitTime;
};

