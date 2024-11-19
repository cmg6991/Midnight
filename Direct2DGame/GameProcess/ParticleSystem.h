#pragma once
#include "Component.h"
#include "ParticleDefine.h"
class GameObject;
class Transform;

/// <summary>
/// 고민1. 파티클 ~ 새 클래스 or 게임오브젝트 -> 일단은 2
/// 고민2. 씬에 파티클을 등록시켜야 하는가 -> 일단 y
/// 
/// 2023 07 27
/// </summary>

using namespace ps;


// 파티클을 방출하는 컴포넌트 클래스
class ParticleSystem :  public Component
{
/// 생성자와 소멸자  ===================================================================
public:
	ParticleSystem(); 
	~ParticleSystem();

	Component* Clone() override;

	void Start() override;

///맴버 함수  =========================================================================
public:
	void LateUpdate(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer) override;
	void DebugRender(D2DRenderer* _d2DRendere) override;

	void Play() { m_isPlaying = true; m_durationTimer = 0.f; }
	void Stop();
	void AddParticle(GameObject* _obj); //파티클 종류 추가
	void AddDefaultParticle(const wstring& imageKey);
	GameObject* GetParticlePrefab(UINT index) {	if (m_container.size() <= index) return nullptr;
											return m_container[index]; }
		
	void Remove();
	
	void SubEmit(GameObject* particle);	//파티클 클래스 에서만 이걸 호출하게 하고싶다..


private:
	//파티클 생성 관련 함수
	void Generate();
	
	void SetSquarePosNDir(Vector2& pos, Vector2& direction);
	void SetCirclePosNDir(Vector2& pos, Vector2& direction);
	void SetConePosNDir(Vector2& pos, Vector2& direction);

	void setRandomValue(const ParticleValue& value, float& result);
	void setRandomValue(const VarianceValue& value, float& result);
	

	// 랜덤 함수
	float LinearRandom(const float& min, const float& max);
	float NormalRandom(const float& min, const float& max);
	//float DiscreteRandom();


///맴버 변수 =========================================================================

	//--------------------------------------------------------------------
	//								시스템 변수 
	//--------------------------------------------------------------------
private:
	Transform* m_transform;				// 부모의 transform
	vector<GameObject*> m_container;	// 방출할 파티클 종류 리스트

	UINT m_typeCount;					// 파티클 종류 수
	UINT m_count;						// 현재 존재하는 파티클 수
	float m_durationTimer;				// 내부 시간
	float m_emissionTimer;				// 내부 시간
	float m_nextEmissionTime;			// 내부 시간
	bool m_isPlaying = false;			// 지금 파티클이 방출되고 있는지 // play on awake?
	
	// 랜덤 변수
	std::random_device rd;
	std::mt19937 gen;

	//--------------------------------------------------------------------
	//							   파티클 기본 변수 
	//--------------------------------------------------------------------
public:
	EMISSION_SHAPE m_shape = EMISSION_SHAPE::CIRCLE; // 파티클의 방출 모형
	//이렇게 해도 되는지 모르겠다 ㅇㅅㅇ
	float m_rotation = 0;					// Square ~ 방향..인데 이게맞나
	float m_halfWidth = 100;				// SQUARE ~ 너비 절반
	float m_halfHeight = 100;				// Square ~ 높이 절반
	
	float &m_radius = m_rotation;			// CONE, CIRCLE ~ 반지름
	float &m_minDegree = m_halfWidth;		// CONE ~ 최소 각
	float &m_maxDegree = m_halfHeight;		// CONE ~ 최대 각

	Vector2 m_centerPos;
	Vector2 m_offset = Vector2(0,0);	// 부모와 위치 offset	

	UINT m_maxCount = 1000;				// 최대로 가질 수 있는 파티클 수
	bool m_isRepeat = true;				// 반복 여부

	float m_duration = 5;				// 방출될 시간
	float m_delayTime = 0;				// 시작 트리거 후 방출까지 지연시간
	ParticleValue m_emitInterval;		// 방출 간격(시간)
	//bool preWarm;	
	END_ACTION m_endAction = END_ACTION::SLEEP;	// 방출이 끝난 후 행동 (Destroy일 경우 부모 오브젝트 삭제)	

	///사각형일때 높이에따른 랜덤 (임시..)
	RANDOM_TYPE m_SQUAREHeightRandom = RANDOM_TYPE::LINEAR;


	//--------------------------------------------------------------------
	//                          파티클 세부 변수 
	//--------------------------------------------------------------------
	
	bool m_isCollide = false;			// 충돌 판정 여부
	float m_gravity = 0;				// 중력 계수, 0이면 중력x (진짜 중력은 아니고 눈속임만)
	ParticleValue m_lifeTime;			// 삭제까지의 시간
	
	ParticleValue m_initScale;			// 초기 크기 값
	VarianceValue m_scaleVariance;		// 크기 변화량

	ParticleValue m_initSpeed;			// 초기 속도 값
	VarianceValue m_speedVariance;		// 속도 변화량

	ParticleValue m_initRotation;		// 초기 회전 값
	VarianceValue m_rotationVariance;   // 회전 변화량

	ParticleValue m_initAlpha;			// 초기 알파 값
	VarianceValue m_AlphaVariance;		// 알파 변화량

	/// 함수포인터로 사용자정의 함수 받기


	//--------------------------------------------------------------------
	//								Sub Emitters
	//--------------------------------------------------------------------

	bool m_subEmit = false;
	TRIGGER m_subEmitTrigger = TRIGGER::TIME;
	float m_subEmitTime = 0.04f;

	//bool m_inherit; // 상속 : lifetime, size, ...
	//UINT m_subEmditProbablity;
};

