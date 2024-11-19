#pragma once
#include <MonoBehaviour.h>
class EndingParticle : public MonoBehaviour
{
public:
	EndingParticle();
	~EndingParticle();
	Component* Clone();

public:
	void Start() override;
	void Update(float _deltaTime) override;

private:
	Particle* m_particle;
	Transform* m_transform;
	PointLightRenderer* m_light;

	float m_lifeTime;
	float m_quaterTime;

	Vector2 m_direction;
	float m_speed;
	float m_maxAlpha;
};

