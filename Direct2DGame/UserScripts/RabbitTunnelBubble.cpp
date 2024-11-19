#include "UserScriptsPCH.h"
#include "RabbitTunnelBubble.h"
#include "RabbitTunnel.h"

RabbitTunnelBubble::RabbitTunnelBubble()
	: MonoBehaviour(typeid(this).name()), m_rabbitTunnel(nullptr), m_textureRenderer(nullptr), m_transform(nullptr)
{

}

RabbitTunnelBubble::~RabbitTunnelBubble()
{

}

Component* RabbitTunnelBubble::Clone()
{
	RabbitTunnelBubble* clone = new RabbitTunnelBubble();

	return clone;
}

void RabbitTunnelBubble::Start()
{
	m_rabbitTunnel = GetGameObject()->GetParent();

	m_transform = GetComponent<Transform>();
	m_textureRenderer = CreateComponent<TextureRenderer>();
/*	m_position=m_rabbitTunnel->GetComponent<Transform>()->GetPosition();*/
	
	m_transform->SetOffset(Vector2(0.f,130.f));
	m_renderTime = 2.f;
	
}

void RabbitTunnelBubble::Update(float _deltaTime)
{
	if (m_rabbitTunnel->GetComponent<RabbitTunnel>()->GetisPlayer())
	{
		m_textureRenderer->SetAlpha(1.0f);
		m_textureRenderer->SetKey(L"100");
	
	}
	else
	{
		m_textureRenderer->SetAlpha(0.0f);
	}

}

void RabbitTunnelBubble::Render(D2DRenderer* _d2DRenderer)
{

}
