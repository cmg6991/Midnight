#include "UserScriptsPCH.h"
#include "EndingParticle.h"
#include <random>

EndingParticle::EndingParticle()
	: MonoBehaviour(typeid(this).name())
	,m_particle(nullptr), m_lifeTime(0.f), m_quaterTime(0.f)
{
}

EndingParticle::~EndingParticle()
{
}

Component* EndingParticle::Clone()
{
	Component* clone = new EndingParticle();
	return clone;
}

void EndingParticle::Start()
{
	m_transform = GetComponent<Transform>();
	m_particle = GetComponent<Particle>();
	m_light = GetComponent<PointLightRenderer>();

	m_lifeTime = m_particle->GetLifeTime();
	m_quaterTime = m_particle->GetLifeTime() / 4.f;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(20, 30);
	m_speed = dis(gen);

	std::uniform_real_distribution<float> dis2(-1, 1);
	m_direction.x = dis2(gen);
	m_direction.y = dis2(gen);
	m_direction.Normalize();
}

void EndingParticle::Update(float _deltaTime)
{
	
	float time = m_particle->GetTimer();
	if (time < m_quaterTime)
	{
		//알파값 증가
		float alpha = FMath::Lerp(0, 0.7, time / m_quaterTime);
		m_particle->SetAlpha(alpha);

		//밝기 증가
		float light = FMath::Lerp(0, 0.8f, time / m_quaterTime);
		m_light->SetIntensity(light);
	}
	else if (m_quaterTime * 3 < time)
	{
		//알파값 감소
		float alpha = FMath::Lerp(0.7, 0, (time - m_quaterTime * 3) / m_quaterTime);
		m_particle->SetAlpha(alpha);

		//밝기 감소
		float light = FMath::Lerp(0.8, 0.f, time / m_quaterTime);
		m_light->SetIntensity(light);
	}

	// 이동
	Vector2 pos = m_transform->GetPosition();
	pos += m_direction * m_speed * _deltaTime;
	m_transform->SetPosition(pos);
}
