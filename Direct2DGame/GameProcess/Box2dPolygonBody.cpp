//#include "GameProcessPCH.h"
//#include "Box2dPolygonBody.h"
//#include "GameObject.h"
//#include "ManagerSet.h"
//#include "PhysicsManager.h"
//#include "Transform.h"
//#include "CollisionManager.h"
//
////b2FrictionJoint
//
//float Box2dPolygonBody::m_simulationScale = 0.025f;
//float Box2dPolygonBody::m_simulationInvScale = 40.f;
//
//Box2dPolygonBody::Box2dPolygonBody()
//	:Component(CALL_ORDER::BOX2D_COLLIDER, typeid(this).name())
//	,m_currentCollision(0), m_isActive(true), m_body(nullptr)
//{	
//	/// BodyDef 초기화
//	m_bodyDef.type = b2_dynamicBody; // 물체의 유형 (정적, 동적 등)
//	m_bodyDef.position.Set(0.f,0.f); // 초기 위치 설정 (미터 단위)
//	m_bodyDef.angle = 0.0f; // 초기 각도 설정 (라디안 단위)
//	m_bodyDef.linearVelocity.Set(0.0f, 0.0f); // 초기 선속도 설정 (미터/초 단위)
//	m_bodyDef.angularVelocity = 0.0f; // 초기 각속도 설정 (라디안/초 단위)
//	m_bodyDef.linearDamping = 1.f; // 선속도 감속률
//	m_bodyDef.angularDamping = 0.0f; // 각속도 감속률
//	m_bodyDef.fixedRotation = true; // 회전 제한 여부
//	m_bodyDef.bullet = false; // 빠른 이동체 처리 여부
//	//m_bodyDef.userData = static_cast<void*>(GetGameObject()); // 사용자 지정 데이터 (예: 객체 식별자
//
//
//	/// 모양 초기화
//	m_box.SetAsBox(m_halfScale.x * m_simulationScale
//		, m_halfScale.y * m_simulationScale); //너비절반, 높이 절반
//
//	/// FixtureDef 초기화
//	m_fixtureDef.shape = &m_box; // 물체의 형상을 나타내는 b2Shape 객체
//	m_fixtureDef.density = 1.0f; // 밀도 설정
//	m_fixtureDef.friction = 0.2f; // 마찰력 설정
//	m_fixtureDef.restitution = 0.f; // 반발력(탄성) 설정 (0:완전 비탄성 충돌, 1 : 완전 탄성충돌)
//	m_fixtureDef.isSensor = false; // 센서 여부 설정
//	
// 
//}
//
//
//
//void Box2dPolygonBody::CreateBody()
//{
//	/// 충돌 마스크 설정 <TODO>
//	SetMask();
//
//	///충돌 콜백을 받기위한 게임오브젝트 연결
//	m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(GetGameObject());
//	
//	/// 질량 초기화
//	m_box.ComputeMass(&m_massData, m_fixtureDef.density);
//	
//	///body 생성
//	m_body = GetManagerSet()->GetPhysicsManager()->InstanceBody(m_bodyDef);
//	m_body->CreateFixture(&m_fixtureDef);
//
//	//오프셋 설정
//	//m_body->
//}
//
//
//
//Box2dPolygonBody::~Box2dPolygonBody()
//{
//	
//}
//
//
//
//Component* Box2dPolygonBody::Clone()
//{
//	///TODO
//	return nullptr;
//}
//
//
//
//void Box2dPolygonBody::SetUp(Vector2 _scale, b2BodyType _type, bool _isTrigger, Vector2 _offset)
//{
//	m_offset = _offset;
//	///TODO offset사용하기
//
//	// 위치 초기화
//	m_position = GetComponent<Transform>()->GetPosition();
//	m_bodyDef.position.Set(m_position.x * m_simulationScale
//		, m_position.y * m_simulationScale);
//	
//	// 크기 초기화
//	m_halfScale = _scale * 0.5;
//	m_box.SetAsBox(m_halfScale.x * m_simulationScale
//		, m_halfScale.y * m_simulationScale);
//
//	m_bodyDef.type = _type;
//	m_fixtureDef.isSensor = _isTrigger;
//}
//
//void Box2dPolygonBody::DebugRender(D2DRenderer* _d2DRenderer)
//{
//	Vector2 centerPos = GetComponent<Transform>()->GetPosition();
//
//	Vector2 leftTop = Vector2(centerPos.x - m_halfScale.x, centerPos.y + m_halfScale.y);
//	Vector2 rightBottom = Vector2(centerPos.x +  m_halfScale.x, centerPos.y - m_halfScale.y);
//
//	if(m_currentCollision == 0)
//		_d2DRenderer->DrawRectangle(leftTop,rightBottom,D2D1::ColorF::PaleGreen);
//	else
//		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Red);
//}
//
//
//void Box2dPolygonBody::Finalize()
//{
//	GetManagerSet()->GetPhysicsManager()->DeleteBody(m_body);
//}
//
//void Box2dPolygonBody::FixedUpdate(float _fixedDeltaTime)
//{
//	assert(m_body != nullptr || !L"\n값 설정 후 CreateBody를 해주세요!! 반대 순서는 안됨");
//
//	//body postion -> transform 
//	Vector2 centerPos;
//	centerPos.x = m_body->GetPosition().x * m_simulationInvScale;
//	centerPos.y = m_body->GetPosition().y * m_simulationInvScale;
//
//	GetComponent<Transform>()->SetPosition(centerPos);
//
//
//	//게임오브젝트에 충돌중임을 알림
//	for (auto obj : m_collidingObjs)
//	{
//		GetGameObject()->OnBox2dCollisionStay(obj);
//	}
//
//	// 	///테스트용
//	// 	if (GetGameObject()->GetName() == "ground")
//	// 	{
//	// 		Vector2 pos = GetComponent<Transform>()->GetPosition();
//	// 		pos += Vector2(200, 0) * _deltaTime;
//	// 		SetPositionOnSimulating(pos);
//	// 	}
//}
//
//void Box2dPolygonBody::SetLinearXVelocity(float _velocity)
//{
//	b2Vec2 velocity = m_body->GetLinearVelocity();
//	velocity.x = _velocity;
//	m_body->SetLinearVelocity(b2Vec2(velocity.x * m_simulationScale, velocity.y));
//}
//
//void Box2dPolygonBody::SetLinearYVelocity(float _velocity)
//{
//	b2Vec2 velocity = m_body->GetLinearVelocity();
//	velocity.y = _velocity;
//	m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y * m_simulationScale));
//}
//
//void Box2dPolygonBody::OnBox2dCollisionEnter(GameObject* _otherObj)
//{
//	m_currentCollision++;
//	m_collidingObjs.push_back(_otherObj);
//}
//
//void Box2dPolygonBody::OnBox2dCollisionStay(GameObject* _otherObj)
//{
//	
//}
//
//void Box2dPolygonBody::OnBox2dCollisionExit(GameObject* _otherObj)
//{
//	m_currentCollision--;
//	remove(m_collidingObjs.begin(), m_collidingObjs.end(), _otherObj);
//}
//
//void Box2dPolygonBody::SetMask()
//{
//	OBJECT_TYPE type = GetGameObject()->GetObjectType();
//	unsigned int bits = 1 << (static_cast<int>(type));
//	unsigned int maskBits = GetCollisionManager()->GetCheckType(type);
//
//	m_fixtureDef.filter.categoryBits = bits; // 충돌 필터 범주 설정
//	m_fixtureDef.filter.maskBits = maskBits; // 충돌 필터 마스크 설정
//	m_fixtureDef.filter.groupIndex = 0; // 충돌 그룹 설정
//}
