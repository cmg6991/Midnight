#pragma once
#include <MonoBehaviour.h>
class DecoFog : public MonoBehaviour
{
public:
	DecoFog();
	~DecoFog();
	Component* Clone() override;
	void Start() override;

public:
	void Update(float _deltaTime) override;

private:
	Particle* m_particle;
	float m_lifeTime; 
	float m_quaterTime;
};

