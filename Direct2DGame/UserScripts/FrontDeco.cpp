#include "UserScriptsPCH.h"
#include "FrontDeco.h"

FrontDeco::FrontDeco()
	:m_textureRenderer(nullptr), m_state(0)
{
	
}

FrontDeco::~FrontDeco()
{
}

Component* FrontDeco::Clone()
{
	return nullptr;
}

void FrontDeco::Update(float _deltaTime)
{
	if (m_state == 1)
	{
		float alpha = m_textureRenderer->GetAlpha();
		alpha = Vector2::Lerp(Vector2(alpha,alpha), Vector2(1, 1), _deltaTime * 3).x;
		if (0.99 < alpha) { alpha = 1; m_state = 0; }
		m_textureRenderer->SetAlpha(alpha);
	}
	else if (m_state == -1)
	{
		float alpha = m_textureRenderer->GetAlpha();
		alpha = Vector2::Lerp(Vector2(alpha, alpha), Vector2(m_alphaHold, m_alphaHold), _deltaTime * 3).x;
		if (alpha < m_alphaHold - 0.01) { alpha = m_alphaHold; m_state = 0; }
		m_textureRenderer->SetAlpha(alpha);
	}
}

void FrontDeco::OnTriggerEnter(const Collision& _collision)
{
	m_state = -1;
	m_textureRenderer = GetComponent<TextureRenderer>();
}

void FrontDeco::OnTriggerExit(const Collision& _collision)
{
	m_state = 1;
}
