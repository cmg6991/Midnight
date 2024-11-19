//#pragma once
//#include "Component.h"
//
////
////enum class Box2D_CATEGORY
////{
////	DEFAULT =			0b0000'0000'0000'0001, //1
////	PLAYER =			0b0000'0000'0000'0010, //2
////	TILE =				0b0000'0000'0000'0100, //4
////	INTERACTOVE_ITEM =  0b0000'0000'0000'1000, //8
////	CHASER =			0b0000'0000'0001'0000, //16
////	//CHASER_BLOCKER,
////};
////
////enum class Box2D_MASK
////{
////	DEFAULT =			0b1111'1111'1111'1111, 
////	PLAYER =			0b0000'0000'0001'1101, 
////	TILE =				0b0000'0000'0000'0010,   
////	INTERACTOVE_ITEM =	0b0000'0000'0000'0010,
////	CHASER =			0b0000'0000'0000'0010,
////	//CHASER_BLOCKER,
////};
//
//
///// <summary>
///// Box2d에서 사용되는 body를 감싼 Collider
///// </summary>
//class Box2dPolygonBody : public Component
//{
//// 생성자와 소멸자 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//public:
//	Box2dPolygonBody();
//	~Box2dPolygonBody();
//	Component* Clone() override;
//
//	void SetUp(Vector2 _scale, b2BodyType _type, bool _isTrigger, Vector2 _offset = Vector2());
//
///// 맴버 함수 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//public:
//	void DebugRender(D2DRenderer* _d2DRenderer) override;
//	void Finalize() override;
//	void FixedUpdate(float _fixedDeltaTime) override;
//
//	//실행 전ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	b2Body* getBody() { return m_body; }
//
//	Vector2 GetPosition() { m_body->GetPosition(); }
//
//	void SetOffset(Vector2 _offset) { m_offset = _offset; }
//	Vector2 GetOffset() { return m_offset; }
//	
//	void SetScale(Vector2 _scale) {};
//	void SetFixedRotation(bool _arg) { m_bodyDef.fixedRotation = _arg; }
//	void SetDensity(float _density) { m_fixtureDef.density = _density; }
//	void SetFriction(float _friction) { m_fixtureDef.friction = _friction; }
//	void SetRestitution(float _restitution) { m_fixtureDef.restitution = _restitution; }
//	void SetGravityScale(float _arg) { m_bodyDef.gravityScale = _arg; }
//
//	void CreateBody();
//	
//	/*
//	b2_staticBody : 움직이지 않을 물체
//	b2_kinematicBody : 물리의 영향을 받지 않고 직접 프로그래밍 할 물체
//	b2_dynamicBody : 물리의 영향을 받는 물체
//	*/
//	void SetType(b2BodyType _type) { m_bodyDef.type = _type; };
//	void SetTrigger(bool _isTrigger) { m_fixtureDef.isSensor = _isTrigger; }
//	bool IsTrigger() const { return m_fixtureDef.isSensor; }
//
//	bool IsActive() const { return m_isActive; }
//	void SetActive(bool _isActive) { m_isActive = _isActive; }
//
//	//실행 도중 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	void SetPositionOnSimulating(Vector2 _pos) { m_body->SetTransform(b2Vec2(_pos.x * m_simulationScale, _pos.y * m_simulationScale), 0.f); }
//	void SetLinearVelocity(Vector2 _vector) { m_body->SetLinearVelocity(b2Vec2(_vector.x * m_simulationScale, _vector.y * m_simulationScale)); }
//	void SetLinearXVelocity(float _velocity);
//	void SetLinearYVelocity(float _velocity);
//	void ApplyForceToCenter(Vector2 _force)	{ m_body->ApplyForceToCenter(b2Vec2(_force.x * m_simulationScale, _force.y * m_simulationScale), true); }
//	void ApplyLinearImpulseToCenter(Vector2 _impulse)	{m_body->ApplyLinearImpulseToCenter(b2Vec2(_impulse.x * m_simulationScale, _impulse.y * m_simulationScale), true);}
//
//
//	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//	///Box2d 충돌 관련 함수
//	void OnBox2dCollisionEnter(GameObject* _otherObj) override;
//	void OnBox2dCollisionStay(GameObject* _otherObj) override;
//	void OnBox2dCollisionExit(GameObject* _otherObj) override;
//
//private:
//	void SetMask();
//
///// 맴버 변수 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//private:
//	int m_currentCollision; // 현재 충돌중인 갯수
//	vector<GameObject*> m_collidingObjs;
//
//	Vector2 m_offset;		// 위치 오프셋
//	Vector2 m_position;		// 위치
//
//	bool m_isActive;		// 콜라이더의 활성화 상태 여부
//
//	b2Body* m_body;
//	b2BodyDef m_bodyDef;
//	b2FixtureDef m_fixtureDef;
//	
//	b2PolygonShape m_box;
//	b2MassData m_massData;
//
//	static float m_simulationScale;
//	static float m_simulationInvScale;
//
////디버깅용 변수?
//	Vector2 m_halfScale = Vector2(100,100);
//};
//
