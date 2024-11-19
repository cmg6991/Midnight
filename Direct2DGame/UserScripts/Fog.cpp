#include "UserScriptsPCH.h"
#include "Fog.h"
#include "Button.h"

Fog::Fog() 
	:MonoBehaviour(typeid(this).name())
	, m_textureRenderer(nullptr)
	, m_button(nullptr)
	, m_buttonConmponent(nullptr)
	, m_alpha(0.f)
{

}

Fog::~Fog()
{

}

Component* Fog::Clone()
{
	Fog* clone = new Fog();

	return clone;
}

void Fog::Start()
{
	m_textureRenderer = GetComponent<TextureRenderer>();

	m_buttonConmponent = m_button->GetComponent<Button>();
	m_alpha = 1.f;
}

void Fog::Update(float _deltaTime)
{

	if (m_buttonConmponent->GetSwitchOn())
	{
		m_alpha-=0.5f* _deltaTime;
		m_textureRenderer->SetAlpha(m_alpha);
	}

}

void Fog::Render(D2DRenderer* _d2DRenderer)
{

}

void Fog::PostRender(D2DRenderer* _d2DRenderer)
{

}

void Fog::DebugRender(D2DRenderer* _d2DRenderer)
{

}
