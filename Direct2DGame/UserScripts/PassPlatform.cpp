#include "UserScriptsPCH.h"
#include "PassPlatform.h"
#include "PlayerComponent.h"
#include "RabbitComponent.h"

PassPlatform::PassPlatform()
	:MonoBehaviour(typeid(this).name())
	,m_player(nullptr)
	,m_playerComponent(nullptr)
	,m_rabbit(nullptr)
	,m_rabbitComponent(nullptr)
	,m_playerBox(nullptr)
	,m_rabbitBox(nullptr)
	,m_platformBox(nullptr)
{

}

PassPlatform::~PassPlatform()
{

}

Component* PassPlatform::Clone()
{
	PassPlatform* clone = new PassPlatform();
	clone->m_platformBox = nullptr;
	clone->m_player = m_player;
	clone->m_rabbit = m_rabbit;
	
	return clone;
}

void PassPlatform::Start()
{
	m_playerComponent = m_player->GetComponent<PlayerComponent>();
	m_rabbitComponent = m_rabbit->GetComponent<RabbitComponent>();
	m_playerBox = m_player->GetComponent<BoxCollider>();
	m_rabbitBox = m_rabbit->GetComponent<BoxCollider>();

	m_renderer = GetComponent<TextureRenderer>();

	m_platformBox = GetComponent<BoxCollider>();
}

void PassPlatform::Update(float _deltaTime)
{
	bool isInverse = m_playerComponent->GetIsInverseGravity();
	bool playerActive = m_playerComponent->IsPlayerActive();

	if ( playerActive && !isInverse) // 플레이어 일반 중력
	{
		float playerMinY = m_playerBox->GetMinPoint().y;
		float platformMaxY =  m_platformBox->GetMaxPoint().y;

		if (playerMinY >= platformMaxY - OFFSET)
		{
			m_platformBox->SetActive(true);
		}
		else
		{
			m_platformBox->SetActive(false);
		}

	}
	else if (playerActive && isInverse) // 플레이어 역중력 
	{

		float playerMaxY = m_playerBox->GetMaxPoint().y;
		float platformMinY = m_platformBox->GetMinPoint().y;

		if (playerMaxY <= platformMinY + OFFSET)
		{
			m_platformBox->SetActive(true);
		}
		else
		{
			m_platformBox->SetActive(false);
		} 
		
	}
	else if ( !playerActive && !isInverse) // 토끼 중력 
	{

		float rabbitMinY = m_rabbitBox->GetMinPoint().y;
		float platformMaxY = m_platformBox->GetMaxPoint().y;
		
		if (rabbitMinY >= platformMaxY - OFFSET)
		{
			m_platformBox->SetActive(true);
		}
		else
		{
			m_platformBox->SetActive(false);
		}

	}
	else if (!playerActive && isInverse) // 토끼 역중력 
	{

		float rabbitMaxY = m_rabbitBox->GetMaxPoint().y;
		float platformMinY = m_platformBox->GetMinPoint().y;

		if (rabbitMaxY <= platformMinY + OFFSET)
		{
			m_platformBox->SetActive(true);
		}
		else
		{
			m_platformBox->SetActive(false);
		}

	}




}

void PassPlatform::Render(D2DRenderer* _d2DRenderer)
{
	Vector2 position =  m_platformBox->GetPosition();
	Vector2 scale =m_platformBox->GetScale();

	/*if (m_platformBox->IsActive())
	{
		m_renderer->SetAlpha(1.f);
	}
	else
	{
		m_renderer->SetAlpha(0.5f);
	}*/
}
