#include "GameProcessPCH.h"
#include "BaseFSM.h"
#include "BaseStatement.h"
#include "GameObject.h"
#include "Transform.h"

BaseFSM::BaseFSM()
{
}

BaseFSM::~BaseFSM()
{
	for (auto arg : m_allTransitions)
	{
		delete arg.second;
	}
}

Component* BaseFSM::Clone()
{
	BaseFSM* clone = new BaseFSM();
	
	///TODO
	
	return clone;
}

void BaseFSM::SetInitState(wstring _name)
{
	m_currentState = FindState(_name);
	m_currentState->OnStateEnter();
}

void BaseFSM::Update(float _deltaTime)
{
	m_currentState->OnStateExcution();
	m_currentState->Update(_deltaTime);
}

void BaseFSM::DebugRender(D2DRenderer* _d2DRenderer)
{
	wstring name = L"상태 : " + m_currentState->getName();
	Vector2 pos = GetComponent<Transform>()->GetPosition() + Vector2(-40,70);
	_d2DRenderer->DrawTextW(name, pos, pos + Vector2(300, 0));
}

void BaseFSM::StateTransistion(wstring _key)
{
	m_currentState->OnStateExit();
	m_currentState = FindState(_key);
	
	//없으면 에러를 띄운다
	assert(nullptr != m_currentState || !L"해당 state가 없습니다.");
	m_currentState->OnStateEnter();
}

wstring BaseFSM::GetCurrentStateName()
{
	return m_currentState->getName(); 
}


BaseStatement* BaseFSM::FindState(wstring _key)
{
	//찾는다
	auto iter = m_allTransitions.find(_key);

	if (iter != m_allTransitions.end())
	{
		return iter->second;
	}
	return nullptr;
}
