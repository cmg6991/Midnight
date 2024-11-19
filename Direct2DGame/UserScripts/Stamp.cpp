#include "UserScriptsPCH.h"
#include "Stamp.h"
#include "PlayerComponent.h"

Stamp::Stamp()
	:MonoBehaviour(typeid(this).name())
	, m_boxCollider(nullptr)
	, m_playerComponent(nullptr)
	, m_player(nullptr)
	, m_transform(nullptr)
{

}

Stamp::~Stamp()
{

}

Component* Stamp::Clone()
{
	Stamp* clone = new Stamp();
	clone->m_player = m_player;
	clone->m_playerComponent = m_playerComponent;

	return clone;
}

void Stamp::Start()
{
	m_boxCollider = GetComponent<BoxCollider>();
	m_playerComponent = m_player->GetComponent<PlayerComponent>();
	m_transform = GetComponent<Transform>();


}

void Stamp::Update(float _deltaTime)
{
	if (m_playerComponent->GetIsInverseGravity())
	{
		m_boxCollider->SetScale(Vector2(200.f, 1080.f));
		m_boxCollider->SetOffset(Vector2(0.f, 490.f));
	}
	else
	{
		m_boxCollider->SetScale(Vector2(500.f, 200.f));
		m_boxCollider->SetOffset(Vector2(150.f, 50.f));

	}

}

void Stamp::Render(D2DRenderer* _d2DRenderer)
{
	Vector2 position = m_transform->GetPosition();

	// 역중력 상태 일어남 
	if (m_playerComponent->GetIsInverseGravity())
	{
		position.y += 490.f;
		_d2DRenderer->DrawBitmap(L"Stamp", position);
	}
	else // 누움 
	{
		position.x += 150.f;
		position.y += 50.f;
		_d2DRenderer->DrawBitmap(L"Stamp2", position);
	}

}

