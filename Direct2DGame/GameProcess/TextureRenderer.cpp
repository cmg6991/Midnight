#include "GameProcessPCH.h"
#include "TextureRenderer.h"
#include "Transform.h"
#include "GameObject.h"

TextureRenderer::TextureRenderer()
	:Component(CALL_ORDER::RENDERER, typeid(this).name())
	, m_transform(nullptr)
	, m_alpha(1.f), m_offset{}, m_textKey{}
	, m_scale(Vector2::One)
	, m_flipType(FLIP_TYPE::NONE)
{

}

TextureRenderer::~TextureRenderer()
{

}

Component* TextureRenderer::Clone()
{
	TextureRenderer* clone = new TextureRenderer();
	clone->m_alpha = m_alpha;
	clone->m_offset = m_offset;
	clone->m_textKey = m_textKey;

	return clone;
}

void TextureRenderer::Render(D2DRenderer* _d2DRenderer)
{
	/// textKeyÀÌ ¾øÀ½
	if (m_textKey.empty())
		return;

	Vector2 position = m_transform->GetPosition() + m_offset;
	float rotation = m_transform->GetRotation();

	_d2DRenderer->DrawBitmap(m_textKey, position, rotation, m_alpha, m_flipType,m_scale);
}


void TextureRenderer::Start()
{
	m_transform = GetComponent<Transform>();

	assert(m_transform);
}
