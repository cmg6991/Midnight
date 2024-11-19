#include "UserScriptsPCH.h"
#include "StandLightFootSwitch.h"

StandLightFootSwitch::StandLightFootSwitch()
	:MonoBehaviour(typeid(this).name())
	, m_isFootSwitchOn(false)

{

}

StandLightFootSwitch::~StandLightFootSwitch()
{

}

Component* StandLightFootSwitch::Clone()
{
	StandLightFootSwitch* clone = new StandLightFootSwitch();
	return clone;
}

void StandLightFootSwitch::Start()
{

}

void StandLightFootSwitch::Update(float _deltaTime)
{

}

void StandLightFootSwitch::OnCollisionEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		SetFootSwitchOn(true);
	}
}
void StandLightFootSwitch::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		SetFootSwitchOn(true);
	}
}


void StandLightFootSwitch::OnCollisionExit(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		SetFootSwitchOn(false);
	}
}
