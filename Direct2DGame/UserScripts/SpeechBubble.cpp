#include "UserScriptsPCH.h"
#include "SpeechBubble.h"

SpeechBubble::SpeechBubble()
	:MonoBehaviour(typeid(this).name())
	, m_position(Vector2::Zero)
	, m_offset(Vector2::Zero)
	, m_textColor(ColorF::Black)
	, m_isShowText(false)
	, m_transform(nullptr)
	, m_background(L"말풍선")
{

}

SpeechBubble::~SpeechBubble()
{

}

Component* SpeechBubble::Clone()
{
	SpeechBubble* clone = new SpeechBubble();
	
	clone->m_isShowText = m_isShowText;
	clone->m_offset = m_offset;
	clone->m_position = m_position;
	clone->m_textOffset = m_textOffset;
	clone->m_textColor = m_textColor;
	clone->m_text = m_text;

	return clone;
}

void SpeechBubble::Start()
{
	m_transform = GetComponent<Transform>();
}

void SpeechBubble::LateUpdate(float _deltaTime)
{
	// 게임오브젝의 포지션 
	Vector2 position = m_transform->GetPosition();

	// 말풍선 포지션 
	m_position = m_offset + position;
}

void SpeechBubble::PostRender(D2DRenderer* _d2DRenderer)
{
	if (m_isShowText)
	{
		_d2DRenderer->DrawBitmap(m_background, m_position);

		const Vector2 textScale{ 500.f,300.f };


		Vector2 textPositioon = m_position + m_textOffset;

		Vector2 leftTop{ textPositioon.x, textPositioon.y };
		Vector2 rightBottom{ textPositioon.x + textScale.x , textPositioon.y - textScale.y };
		 
		ColorF color(85.f / 255.f, 85.f / 255.f, 85.f / 255.f);
		_d2DRenderer->DrawTextW(m_text, leftTop, rightBottom, color, FONT_TYPE::TALK);
	}
}

void SpeechBubble::ShowText(const wstring& _text, ColorF _color /*= ColorF::Black*/)
{
	m_isShowText = true;
	m_text = _text; 
	m_textColor = _color;
}

void SpeechBubble::CloseText()
{
	m_isShowText = false;
}
