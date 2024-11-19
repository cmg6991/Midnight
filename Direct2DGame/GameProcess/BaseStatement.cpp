#include "GameProcessPCH.h"
#include "BaseStatement.h"
#include "GameObject.h"
#include "Component.h"
#include "BaseFSM.h"

BaseStatement::BaseStatement(BaseFSM* _fsm, GameObject* _obj, wstring _nextState)
	: m_nextState(_nextState), m_fsm(_fsm), m_gameObject(_obj)
	, m_timer(0), m_isLoop(false)
{
}
