#include "UserScriptsPCH.h"
#include "RabbitTunnel.h"
#include "RabbitComponent.h"
#include "Chandlier.h"
#include "Factory.h"

RabbitTunnel::RabbitTunnel()
	: MonoBehaviour(typeid(this).name())
	, m_rabbit(nullptr)
	, m_inputManager(nullptr)
	, m_rabbitTunnel(nullptr)
	, m_transform(nullptr)
	, m_cameraManager(nullptr)
	, m_textureRenderer(nullptr)
	, m_isPlayer(false)
	, m_renderTime(0.f)
	, m_isOn(false)
{

}

RabbitTunnel::~RabbitTunnel()
{

}

Component* RabbitTunnel::Clone()
{
	RabbitTunnel* clone = new RabbitTunnel();

	return clone;
}

void RabbitTunnel::Start()
{
	m_cameraManager = GetCameraManager();
	m_inputManager = GetInputManager();
	m_transform = GetComponent<Transform>();
	m_textureRenderer=GetComponent<TextureRenderer>();

	m_position = m_transform->GetPosition();		// ÇöÀç Åä³¢±¼ÀÇ Æ÷Áö¼Ç
	m_objectName=GetGameObject()->GetDebugName();

	// °¡Àå °¡±î¿î Åä³¢±¼ Ã£±â
	const vector<GameObject*>& rabbitTunnel = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::RABBIT_TUNNEL);

	float minimumDistance = FloatMax();

	for (auto tunnel : rabbitTunnel)			// Åä³¢±¼À» µ¹¸é¼­ Ã£´Â´Ù.
	{
		string objName = tunnel->GetDebugName();
		if (m_objectName != objName)
		{
			Vector2 position = tunnel->GetComponent<Transform>()->GetPosition();

			float distance = (m_position - position).Length();

			if (distance <= minimumDistance)
			{
				minimumDistance = distance;
				m_rabbitTunnel = tunnel->GetComponent<RabbitTunnel>();
			}
		}
	}

	m_renderTime = 2.f;
}

void RabbitTunnel::Update(float _deltaTime)
{
	if (m_isPlayer)
	{
		m_renderTime -= 1.f * _deltaTime;
		if (m_renderTime < 0)
		{
			m_isPlayer = false;
			m_renderTime = 2.f;
		}
	}
}

void RabbitTunnel::Render(D2DRenderer* _d2DRenderer)
{

}

void RabbitTunnel::PostRender(D2DRenderer* _d2DRenderer)
{

}

void RabbitTunnel::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 pos = GetComponent<Transform>()->GetPosition();
	string name = m_rabbitTunnel->GetGameObject()->GetDebugName();

	pos.y += 50.f;

	wstring nameW;

	nameW.assign(name.begin(), name.end());

	wstring info = L"¿¬°áµÈ µ¿±¼ : " + nameW;
	_d2DRenderer->DrawTextW(info, pos, Vector2(pos.x + 200.f, pos.y), D2D1::ColorF::DeepPink);
}

void RabbitTunnel::OnCollisionStay(const Collision& _collision)
{
	if (m_inputManager->IsKeyState(KEY::E, KEY_STATE::TAP) && _collision.otherObject->GetName() == "rabbit")
	{
		// Åä³¢±¼ÀÌ Ä«¸Þ¶ó ¹Û¿¡ ÀÖ´Ù
		m_rabbit->GetComponent<Transform>()->SetPosition(m_rabbitTunnel->GetPosition());

	}
	if (m_inputManager->IsKeyState(KEY::E, KEY_STATE::TAP) && _collision.otherObject->GetName() == "player" &&
		m_rabbit->GetComponent<RabbitComponent>()->GetisChangeObject() == false)
	{
			m_isPlayer = true;
	}
}
