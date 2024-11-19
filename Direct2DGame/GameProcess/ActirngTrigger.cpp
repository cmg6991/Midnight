#include "GameProcessPCH.h"
#include "ActirngTrigger.h"
#include "GameObject.h"
#include "DirectManager.h"
#include "Transform.h"

ActirngTrigger::ActirngTrigger()
	:MonoBehaviour(typeid(this).name())
	,m_isActive(false)
	,m_actingNumber(-1)
{

}

ActirngTrigger::~ActirngTrigger()
{

}

Component* ActirngTrigger::Clone()
{
	ActirngTrigger* clone = new ActirngTrigger();
	clone->m_actingNumber = m_actingNumber;

	return clone;
}

void ActirngTrigger::Set(int _actingNumber)
{
	m_actingNumber = _actingNumber;
	m_isActive = true;
}

void ActirngTrigger::OnTriggerStay(const Collision& _collision)
{
	int currentActingOrder = GetDirectManager()->GetCurrentActingOrder();

	// 플레이어와 충돌시에 확인
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER
		&& m_actingNumber == currentActingOrder && m_isActive)
	{
		// 다음 연출을 지시한다.
		GetDirectManager()->FinishActing(m_actingNumber);
		m_isActive = false;
		
		GetGameObject()->Destory();
	}
		
}

void ActirngTrigger::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 position = GetComponent<Transform>()->GetPosition();
	position.y -= 60.f;

	wstring str = L"연출 순서 : " + std::to_wstring(m_actingNumber);
	
	_d2DRenderer->SetCameraAffected(true);
	_d2DRenderer->DrawTextW(str, position, Vector2(position.x +200.f, position.y - 200.f), D2D1::ColorF::Gold);
}
