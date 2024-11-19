#include "UserScriptsPCH.h"
#include "LightWaver.h"

#include "Transform.h"

LightWaver::LightWaver()
	: MonoBehaviour(typeid(this).name())
	, m_transform(nullptr)
	, m_amplitute(150.f)
	, m_frequency(0.005f)
	, m_phaseShift(0.f)
	, m_time(0.f)
	, m_speed(300.f)
{
}

LightWaver::~LightWaver()
{
}

Component* LightWaver::Clone()
{
	LightWaver* clone = new LightWaver();

	return clone;
}
	
void LightWaver::Start()
{
	m_transform = GetComponent<Transform>();
	m_origin = m_transform->GetPosition();
}

void LightWaver::Update(float _deltaTime)
{
	m_time += _deltaTime;

	Vector2 phase;
	phase.x = m_time * m_speed;
	phase.y = m_amplitute * sin(phase.x * m_frequency);
	
	phase += m_origin;

	

	m_transform->SetPosition(GetInputManager()->GetWorldMousePosition());
}
