#include "UserScriptsPCH.h"
#include "SnowFall.h"

SnowFall::SnowFall()
	: MonoBehaviour(typeid(this).name())
	, m_particle(nullptr), m_changeTime(0.f), m_timer(0.f)
{

}

SnowFall::~SnowFall()
{

}

Component* SnowFall::Clone()
{
	Component* clone = new SnowFall();
	return clone;
}

void SnowFall::Update(float _deltaTime)
{

}
