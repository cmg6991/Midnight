#include "UserScriptsPCH.h"
#include "Chandlier.h"
#include "ClearCheck.h"

Chandlier::Chandlier()
	:MonoBehaviour(typeid(this).name())
	,m_isLightOn(false)
	,m_clearCheck(nullptr)
{

}

Chandlier::~Chandlier()
{

}

Component* Chandlier::Clone()
{
	return nullptr;
}

void Chandlier::DebugRender(D2DRenderer* _d2DRenderer)
{
	_d2DRenderer->DrawEllipse(GetComponent<Transform>()->GetPosition(), 2000, D2D1::ColorF::Red);
}

void Chandlier::LightOff()
{
	SetLightOn(false);

	vector<GameObject*>& children = GetGameObject()->GetChildren();

	for (auto& child : children)
	{
		auto light = child->GetComponent<PointLightRenderer>();
		if(light == nullptr)
			continue;

		light->SetLightOn(false);
	}

}

void Chandlier::LightOn()
{
	if (GetLightOn())
		return;

	SetLightOn(true);

	if (m_clearCheck != nullptr)
		m_clearCheck->GetComponent<ClearCheck>()->AddClearIndex();

	vector<GameObject*>& children = GetGameObject()->GetChildren();

	for (auto& child : children)
	{
		auto light = child->GetComponent<PointLightRenderer>();
		if (light == nullptr)
			continue;

		light->SetLightOn(true);
	}
}

