#include "GameProcessPCH.h"
#include "TextRenderer.h"
#include "Transform.h"
#include "GameObject.h"

TextRenderer::TextRenderer()
	:Component(CALL_ORDER::TEXT, typeid(this).name())
	,m_printString()
	,m_scale(Vector2::Zero)
	,m_transform(nullptr)
	,m_color(ColorF::White)
{

}

TextRenderer::~TextRenderer()
{

}

Component* TextRenderer::Clone()
{
	TextRenderer* clone = new TextRenderer();
	clone->m_printString = m_printString;
	clone->m_scale = m_scale;

	return clone;
}

void TextRenderer::Start()
{
	m_transform = GetComponent<Transform>();
}

void TextRenderer::Render(D2DRenderer* _d2DRenderer)
{
	Vector2 position = m_transform->GetPosition();
	Vector2 leftTop{ position.x - m_scale.x * 0.5f, position.y + m_scale.y * 0.5f };
	Vector2 rightBottom{ position.x + m_scale.x * 0.5f, position.y - m_scale.y * 0.5f };

	_d2DRenderer->DrawTextW(m_printString, leftTop, rightBottom,m_color);
}
