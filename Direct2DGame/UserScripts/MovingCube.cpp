#include "UserScriptsPCH.h"
#include "MovingCube.h"

MovingCube::MovingCube()
	:MonoBehaviour(typeid(this).name())
	,m_pushSpeed(100.f)
{

}

MovingCube::~MovingCube()
{

}

Component* MovingCube::Clone()
{

	return nullptr;
}

void MovingCube::OnCollisionStay(const Collision& _collision)
{
	const InputManager* input = GetInputManager();
	

	// 토끼에게는 밀린다
	if (_collision.otherObject->GetName() == "rabbit")
	{

		if (input->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD))
		{
			Vector2 moveDistance = Vector2::Zero;
			moveDistance.x = m_pushSpeed * GetTimeManager()->GetDeltaTime();

			GetComponent<Transform>()->AddPosition(moveDistance);
		}
		else if (input->IsKeyState(KEY::LEFT, KEY_STATE::HOLD))
		{
			Vector2 moveDistance = Vector2::Zero;
			moveDistance.x = -m_pushSpeed * GetTimeManager()->GetDeltaTime();

			GetComponent<Transform>()->AddPosition(moveDistance);
		}
	}
	

}
