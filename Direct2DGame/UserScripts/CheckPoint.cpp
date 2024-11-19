#include "UserScriptsPCH.h"
#include "CheckPoint.h"
#include "ReturnCheckPoint.h"
#include "RabbitComponent.h"

CheckPoint::CheckPoint()
	:MonoBehaviour(typeid(this).name())
	,m_order(0)
	,m_position()
{

}

CheckPoint::~CheckPoint()
{

}

void CheckPoint::Start()
{
	m_position = GetComponent<Transform>()->GetPosition();


}

Component* CheckPoint::Clone()
{
	CheckPoint* clone = new CheckPoint();
	clone->m_order = m_order;
	clone->m_position = m_position;

	return clone;
}

void CheckPoint::OnTriggerEnter(const Collision& _collision)
{
	GameObject* otherObject = _collision.otherObject;

	// 플레이어면 체크 포인트를 기억한다 
	if (otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		if (otherObject->GetName() == "player") // 플레이어인 경우
		{
			otherObject->GetComponent<ReturnCheckPoint>()->SetCheckPoint(m_position, m_order);

		}
		else // 토끼인 경우
		{ 

			GameObject* player = otherObject->GetComponent<RabbitComponent>()->GetMainPlayer();
			player->GetComponent<ReturnCheckPoint>()->SetCheckPoint(m_position, m_order);
		}

		GetGameObject()->Destory();
		
		// TODO :: 체크포인트 효과 


	}
}
