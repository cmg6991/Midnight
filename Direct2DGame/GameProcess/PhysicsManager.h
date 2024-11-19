//#pragma once
//#include "MyContactListener.h"
///// <summary>
///// box2d를 한번 감쌌다.
///// 2023.08.15
///// </summary>
// 
//
/////물리 연산을 담당하는 클래스. 
//class PhysicsManager
//{
/////생성자와 소멸자
//public:
//	PhysicsManager();
//	~PhysicsManager();
//
//	void Initialize();
//
//	void Update(float _deltaTime);
//	void DebugRender(D2DRenderer* _d2dRenderer);
//	void Finalize();
//
//
/////맴버 함수
//public:
//	//b2World* GetWorld() { return m_world; }
//	b2Body* InstanceBody(const b2BodyDef& _bodydef) const;
//	void DeleteBody(b2Body* _body) const { m_world->DestroyBody(_body); }
//
//
/////맴버 변수
//private:
//	b2Vec2 m_gravity; // 중력
//	b2World* m_world;  // rigid body 연산이 일어나는 곳.
//	MyContactListener m_listener; // 충돌 콜백 함수를 받을 객체
//	const float m_timeStep = 1.0f / 50.f; // 물리 연산의 간격( 60hz 권장 ) 
//	const int32 m_velocityIterations = 6;  // 속도 계산을 위한 반복 횟수
//	const int32 m_positionIterations = 2;  // 위치 계산을 위한 반복 횟수
//};
//
