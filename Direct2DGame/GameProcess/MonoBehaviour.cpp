#include "GameProcessPCH.h"
#include "MonoBehaviour.h"

MonoBehaviour::MonoBehaviour(string _name)
	:Component(CALL_ORDER::MONO_BEHAVIOUR,_name)
{}

MonoBehaviour::~MonoBehaviour()
{}
