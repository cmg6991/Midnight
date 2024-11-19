
#include "GameProcessPCH.h"
#include "PointLightRenderer.h"
#include "Transform.h"
#include "GameObject.h"

PointLightRenderer::PointLightRenderer()
	:Component(CALL_ORDER::LIGHT, typeid(this).name())
	,m_scale(Vector2::One)
	,m_angle(0.f)
	,m_currentIntensity(1.f)
	,m_maxIntensity(1.f)
	,m_minimumIntensity(1.f)
	,m_isFixedIntensity(true)
	,m_isIncrease(false)
	,m_intensityChangeSpeed(0.f)
	,m_rgb{1.f,1.f,1.f}
	,m_mode(RENDERING_MODE::RENDER)
	,m_transform(nullptr)
	,m_offset{}
	,m_isLightOn(true)
{

}

PointLightRenderer::~PointLightRenderer()
{
	  
}

Component* PointLightRenderer::Clone()
{
	PointLightRenderer* clone = new PointLightRenderer();
	clone->m_angle = m_angle;
	clone->m_scale = m_scale;
	clone->m_maxIntensity = m_maxIntensity;
	clone->m_mode = m_mode;
	clone->m_rgb = m_rgb;
	clone->m_transform = nullptr;
	clone->m_intensityChangeSpeed = m_intensityChangeSpeed;
	clone->m_isFixedIntensity = m_isFixedIntensity;
	clone->m_minimumIntensity = m_minimumIntensity;
	clone->m_currentIntensity = m_currentIntensity;

	return clone;
}

void PointLightRenderer::Start()
{
	m_transform = GetComponent<Transform>();
	m_currentIntensity = m_maxIntensity;
}

void PointLightRenderer::Update(float _deltaTime)
{
	if (m_isFixedIntensity)
	{
		// 밝기는 맥스로 고정한다.
		m_currentIntensity = m_maxIntensity;
	}
	else if(m_isIncrease)
	{
		m_currentIntensity += m_intensityChangeSpeed * _deltaTime;

		if (m_currentIntensity >= m_maxIntensity)
		{
			m_currentIntensity = m_maxIntensity;
			m_isIncrease = false;
		}
	}
	else
	{
		m_currentIntensity -= m_intensityChangeSpeed * _deltaTime;

		if (m_currentIntensity <= m_minimumIntensity)
		{
			m_currentIntensity = m_minimumIntensity;
			m_isIncrease = true;
		}
	}

}

void PointLightRenderer::PreRender(D2DRenderer* _d2DRenderer)
{
	if (m_mode == RENDERING_MODE::PRE_RENDER)
	{
		PointLightRender(_d2DRenderer);
	}
}

void PointLightRenderer::Render(D2DRenderer* _d2DRenderer)
{
	if (m_mode == RENDERING_MODE::RENDER)
	{
		PointLightRender(_d2DRenderer);
	}
}

void PointLightRenderer::PostRender(D2DRenderer* _d2DRenderer)
{
	if (m_mode == RENDERING_MODE::POST_RENDER)
	{
		PointLightRender(_d2DRenderer);
	}
}

//0xffde71 와 같은 형태로 입력해주면 됩니다
void PointLightRenderer::SetRGB(int color)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	float r_normalized = static_cast<float>(r) / 255.0f;
	float g_normalized = static_cast<float>(g) / 255.0f;
	float b_normalized = static_cast<float>(b) / 255.0f;

	m_rgb = { r_normalized, g_normalized, b_normalized };
}

void PointLightRenderer::PointLightRender(D2DRenderer* _renderer)
{
	if (!m_isLightOn)
		return;

	Vector2 position = m_transform->GetPosition();
	position += m_offset;

	_renderer->DrawPointLight(position, m_currentIntensity, m_rgb,m_scale,m_angle); 
}
