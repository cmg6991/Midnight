#include "UserScriptsPCH.h"
#include "DecoFog.h"

DecoFog::DecoFog()
	: MonoBehaviour(typeid(this).name())
	, m_particle(nullptr), m_quaterTime(0)
{

}

DecoFog::~DecoFog()
{

}

Component* DecoFog::Clone()
{
	Component* clone = new DecoFog();
	return clone;
}

void DecoFog::Start()
{
	m_particle = GetComponent<Particle>();
	m_lifeTime = m_particle->GetLifeTime();
	m_quaterTime =  m_particle->GetLifeTime() / 4.f;
}

void DecoFog::Update(float _deltaTime)
{
	float time = m_particle->GetTimer();
	if (time < m_quaterTime)
	{
		//알파값 증가
		float alpha = FMath::Lerp(0, 1, time / m_quaterTime);
		m_particle->SetAlpha(alpha);
	}
	else if (m_quaterTime * 3 < time)
	{
		//알파값 감소
		float alpha = FMath::Lerp(1, 0, (time - m_quaterTime * 3) / m_quaterTime);
		m_particle->SetAlpha(alpha);
	}
}
