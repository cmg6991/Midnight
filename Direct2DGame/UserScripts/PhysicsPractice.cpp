#include "UserScriptsPCH.h"
//#include "PhysicsPractice.h"
//
//PhysicsPractice::PhysicsPractice()
//	:MonoBehaviour(typeid(this).name()), m_bodyShell(nullptr)
//{
//}
//
//PhysicsPractice::~PhysicsPractice()
//{
//}
//
//void PhysicsPractice::Start()
//{
//	m_bodyShell = GetComponent<Box2dPolygonBody>();
//	m_inputManager = GetManagerSet()->GetInputManager();
//}
//
//void PhysicsPractice::Update(float _dt)
//{
//	if (m_inputManager->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD))
//	{
//		m_bodyShell->SetLinearXVelocity(200);
//// 		Vector2 pos = GetComponent<Transform>()->GetPosition();
//// 		pos += Vector2(200, 0) * _dt;
//// 		m_bodyShell->SetPositionOnSimulating(pos);
//	}
//
//	if (m_inputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD))
//	{
//		m_bodyShell->SetLinearXVelocity(-200);
//// 		Vector2 pos = GetComponent<Transform>()->GetPosition();
//// 		pos += Vector2(-200, 0) * _dt;
//// 		m_bodyShell->SetPositionOnSimulating(pos);
//	}
//
//	if (m_inputManager->IsKeyState(KEY::RIGHT, KEY_STATE::AWAY)
//		|| m_inputManager->IsKeyState(KEY::LEFT, KEY_STATE::AWAY)
//		|| (m_inputManager->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD)
//			&& m_inputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD)))
//	{
//		m_bodyShell->SetLinearXVelocity(0);
//	}
//
//	if (m_inputManager->IsKeyState(KEY::SPACE, KEY_STATE::TAP))
//	{
//		//m_bodyShell->ApplyLinearImpulseToCenter(Vector2(0, 2000));
//		m_bodyShell->SetLinearYVelocity(300);
//	}
//}
//
//void PhysicsPractice::OnBox2dCollisionEnter(GameObject* _otherObj)
//{
//}
//
//void PhysicsPractice::OnBox2dCollisionStay(GameObject* _otherObj)
//{
//
//}
//
//void PhysicsPractice::OnBox2dCollisionExit(GameObject* _otherObj)
//{
//
//}
