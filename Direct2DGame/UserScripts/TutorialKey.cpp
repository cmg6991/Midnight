#include "UserScriptsPCH.h"
#include "TutorialKey.h"

TutorialKey::TutorialKey()
	:MonoBehaviour(typeid(this).name())
	,m_player(nullptr)
{

}

TutorialKey::~TutorialKey()
{

}

Component* TutorialKey::Clone()
{
	return nullptr;
}

void TutorialKey::Start()
{
	m_renderer = GetComponent<TextureRenderer>();

}

void TutorialKey::Update(float _deltaTime)
{
	Vector2 keyPos = GetComponent<Transform>()->GetPosition();
	Vector2 playerPos = m_player->GetComponent<Transform>()->GetPosition();
	
	float distance = (playerPos - keyPos).Length();

	if (distance <= 1000.f)
	{
		if (distance <= 300.f)
			m_renderer->SetAlpha(1.f);
		else
		{
			float ratio =  1.f - (distance - 300.f)/700.f;
			m_renderer->SetAlpha(ratio);
		}
	}
	else
	{
		m_renderer->SetAlpha(0.f);
	}



}
