#pragma once
#include <MonoBehaviour.h>
class SnowFall : public MonoBehaviour
{
public:
	SnowFall();
	~SnowFall();
	Component* Clone() override;

public:
	void Update(float _deltaTime) override;

private:
	Particle* m_particle;
	float m_changeTime;
	float m_timer;

};

