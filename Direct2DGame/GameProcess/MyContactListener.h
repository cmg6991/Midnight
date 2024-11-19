//#pragma once
////#include "b2_world_callbacks.h"
//
//
///// <summary>
///// box2d의 충돌 콜백을 정의
///// </summary>
//class MyContactListener : public b2ContactListener
//{
//public:
//	void BeginContact(b2Contact* contact) override;
//	void EndContact(b2Contact* contact) override;
//
//	/*
//	* 충돌 물리 계산 전에 호출됨
//	//센서(Trigger?)에 대해서는 호출되지 않는다
//	awake body에 대해서만 호출된다.
//	contact points가 0인 경우에도 호출된다(????)
//	contact points를 0으로 설정할 경우 end contact는 호출되지 않는다.
//	하지만 다음 step에서 begin contact가 호출된다(띠용?)
//	Manifold는 충돌 지점, 법선, 침투 깊이 등의 정보를 담고있다.
//	*/
//	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
//
//
//	/*
//	* 충돌 물리 계산 후에 호출됨.
//	solver가 작업을 끝냈을 때 호출된다. impulse를 확인할 때 사용하면 좋다.
//	contact가 touching, solid, awake 일 경우에만 호출된다. 
//	*/
//	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
//};
//
