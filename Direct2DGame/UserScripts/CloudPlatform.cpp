#include "UserScriptsPCH.h"
#include "CloudPlatform.h"

CloudPlatform::CloudPlatform()
	:MonoBehaviour(typeid(this).name())
	,m_startPosition()
	,m_endPosition()
	,m_moveSpeed(20.f)
	,m_positive(false)
	,m_transform(nullptr)
{

}

CloudPlatform::~CloudPlatform()
{

}

Component* CloudPlatform::Clone()
{


	return nullptr;
}

void CloudPlatform::Start()
{
	m_transform = GetComponent<Transform>();
	m_startPosition = m_transform->GetPosition();

	m_endPosition = m_startPosition;
	m_endPosition.y -= 20.f;

}


void CloudPlatform::Update(float _deltaTime)
{


}

void CloudPlatform::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() != OBJECT_TYPE::PLAYER)
		return;

	Vector2 distance{ 0.f , m_moveSpeed * GetTimeManager()->GetDeltaTime() };


	if (m_positive)
	{
		m_transform->AddPosition(distance);
		_collision.otherObject->GetComponent<Transform>()->AddPosition(distance);
		if (m_transform->GetPosition().y >= m_startPosition.y)
		{
			m_positive = !m_positive;
		}

	}
	else
	{
		m_transform->AddPosition(-distance);
		_collision.otherObject->GetComponent<Transform>()->AddPosition(-distance);
		if (m_transform->GetPosition().y <= m_endPosition.y)
		{
			m_positive = !m_positive;
		}
	}

}
