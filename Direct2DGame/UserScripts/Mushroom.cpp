#include "UserScriptsPCH.h"
#include "Mushroom.h"

Mushroom::Mushroom()
	: MonoBehaviour(typeid(this).name())
	, m_BounceTime(2.5f), m_BounceTimer(0), m_touch(false)
	, m_originPos(), m_lowPos()
	, m_amplitute(50.f), m_lastExitTime(0.f), m_timer(0.f)
{

}

Mushroom::~Mushroom()
{

}

Component* Mushroom::Clone()
{
	return 0;
}

void Mushroom::Start()
{
	m_texture = GetComponent<TextureRenderer>();
	m_boxcollider = GetComponent<BoxCollider>();
	m_particleSystem = GetComponent<ParticleSystem>();
	m_rigidBody = GetComponent<RigidBody>();
	m_originPos = m_boxcollider->GetOffset();
	m_lowPos = m_originPos - Vector2(0.f, -20.f);
	m_amplitute = m_originPos.y - m_lowPos.y;
	m_rigidBody->SetMass(50.f);
}

void Mushroom::Update(float _deltaTime)
{
	m_timer += _deltaTime;

	if (m_touch)
	{
		m_BounceTimer += _deltaTime;
		if (m_BounceTime <= m_BounceTimer)
		{
			m_touch = false;
			m_BounceTimer = 0.f;
			m_boxcollider->SetOffset(m_originPos);
			m_texture->SetScale(Vector2(1, 1));
			m_texture->SetOffset(Vector2(0, 0));
		}
		
		float damping = 0.7f;
		float period = 0.2f + 0.08f * m_BounceTimer;
		float y = exp(-damping * m_BounceTimer) * sin(( 1 / period) * m_BounceTimer) * m_amplitute + m_originPos.y;
		m_boxcollider->SetOffset(Vector2(m_originPos.x, y));


		float scale = exp(-damping * m_BounceTimer) * sin((1 / period) * m_BounceTimer) * -0.2 + 1;
		m_texture->SetScale(Vector2(1.f,scale));
		m_texture->SetOffset(Vector2(0.f, - (1 - scale) * 179 * 0.5));
	}
}

void Mushroom::OnCollisionEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() ==OBJECT_TYPE::PLAYER /* && _collision.direct == COLLISION_DIRECT::UP*/)
	{
		if ((m_timer - m_lastExitTime) > 1.f)
		{
			m_touch = true;
			m_particleSystem->Play();

			m_BounceTimer = 0.f;
		}
	}
}

void Mushroom::OnCollisionExit(const Collision& _collision)
{
	m_lastExitTime = m_timer;
}



