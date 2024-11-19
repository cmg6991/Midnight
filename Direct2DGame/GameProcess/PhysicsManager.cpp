//#pragma once
//#include "GameProcessPCH.h"
//#include "PhysicsManager.h"
//#include "MyContactListener.h"
//
//PhysicsManager::PhysicsManager()
//	:m_world(nullptr)
//{
//	m_gravity = b2Vec2(0.f, -9.8f);
//	m_world = new b2World(m_gravity);
//}
//
//PhysicsManager::~PhysicsManager()
//{
//	
//}
//
//void PhysicsManager::Initialize()
//{
//	// 월드 설정
//	m_world->SetContactListener(&m_listener);
//}
//
//void PhysicsManager::Update(float _deltaTime)
//{
//	// transform -> pos, rotation 가져와서 body에 넣기
//	m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
//	// body에서 가져와서 transform  바꾸기?
//}
//
//void PhysicsManager::DebugRender(D2DRenderer* _d2dRenderer)
//{
//
//}
//
//void PhysicsManager::Finalize()
//{
//	delete m_world;
//}
//
//b2Body* PhysicsManager::InstanceBody(const b2BodyDef& _bodydef) const
//{
//	b2Body* body = m_world->CreateBody(&_bodydef);
//	return body;
//}
