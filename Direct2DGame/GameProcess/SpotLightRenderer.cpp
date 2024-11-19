#include "GameProcessPCH.h"
#include "SpotLightRenderer.h"

SpotLightRenderer::SpotLightRenderer()
	:Component(CALL_ORDER::LIGHT, typeid(this).name())
{

}

SpotLightRenderer::~SpotLightRenderer()
{

}
