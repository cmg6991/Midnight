#include "GameProcessPCH.h"
#include "ParticleSystem.h"

#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "TextureRenderer.h"
#include "Animator.h"
#include "Particle.h"
#include "CircleCollider.h"
#include "PointLightRenderer.h"

#include "Scene.h"
#include "SceneManager.h"

using namespace ps;
using namespace FMath;


ParticleSystem::ParticleSystem()
	: Component(CALL_ORDER::PARTICLE_SYSTEM, typeid(this).name())
	, m_transform(nullptr)
	, m_typeCount(0), m_count(0), m_durationTimer(0), m_emissionTimer(0)
	, gen(rd())
	, m_nextEmissionTime(0.f)
{
	//기본값 설정

	m_emitInterval = { 0.2f };
	m_lifeTime = { 3.f };
	m_initScale = { 1.f };
	m_scaleVariance = { 0.f };
	m_initSpeed = { 50.f };
	m_speedVariance = { 0.f };
	m_initRotation = { 0.f };
	m_rotationVariance = { 0.f };
	m_initAlpha = { 1.f };
	m_AlphaVariance = { 0.f };
}

ParticleSystem::~ParticleSystem()
{
	//가지고 있던 파티클 프리팹 삭제
	for (auto i : m_container)
	{
		i->Finalize();
		delete i;
	}
}

Component* ParticleSystem::Clone()
{
	ParticleSystem* clone = new ParticleSystem();
	
	/*clone->m_transform = nullptr;		 

	
	clone->m_particles.clear();
	clone->m_count = 0;
	clone->m_durationTimer = 0;
	clone->m_emissionTimer = 0;
	clone->m_nextEmissionTime = 0;
	clone->m_isPlaying = false;*/

	return clone;
}

void ParticleSystem::Start()
{
	//위치 초기화
	m_transform = GetComponent<Transform>();
	m_centerPos = m_transform->GetPosition();
	m_nextEmissionTime = m_delayTime;
}

void ParticleSystem::LateUpdate(float _deltaTime)
{
	if (m_isPlaying)
	{
		// 포지션 업데이트
		m_centerPos = m_transform->GetPosition() + m_offset;

		// 시간에 따라 방출
		m_emissionTimer += _deltaTime;

		while (m_nextEmissionTime < m_emissionTimer)
		{
			m_emissionTimer -= m_nextEmissionTime;

			if (m_count < m_maxCount)
			{
				Generate();
				m_nextEmissionTime = LinearRandom(m_emitInterval.mininum, m_emitInterval.maximum);
			}
			else
			{
				break;
			}
		}
	}

	//한번 반복이 끝났는지 확인
	if (!m_isRepeat)
	{
		if (m_duration < m_durationTimer)
		{
			m_isPlaying = false;
			m_durationTimer = 0;
			m_emissionTimer = 0;
			
			if(m_endAction == END_ACTION::DESTROY)
				GetGameObject()->Destory();
		}
		else
		{
			m_durationTimer += _deltaTime;
		}
	}
}

void ParticleSystem::Render(D2DRenderer* _d2DRenderer)
{

}

void ParticleSystem::DebugRender(D2DRenderer* _d2DRendere)
{
	std::wstringstream wss;
	wss << m_count;
	wstring c = L"파티클 수 : ";
	c += wss.str();
	_d2DRendere->DrawTextW(c, m_transform->GetPosition()
		, m_transform->GetPosition() + Vector2(300,0));
}

void ParticleSystem::Stop()
{
	m_isPlaying = false;
	m_durationTimer = 0;
	m_emissionTimer = 0;
}

void ParticleSystem::AddParticle(GameObject* _obj)
{
	if (_obj->GetComponent<Particle>() == nullptr)
	{
		//assert();
	}

	m_container.push_back(_obj);
	m_typeCount++;
}

void ParticleSystem::AddDefaultParticle(const wstring& imageKey)
{
	GameObject* obj = new GameObject("particle", GetManagerSet(), OBJECT_TYPE::PARTICLE);
	Transform* transform = obj->CreateComponent<Transform>();
	Particle* particle = obj->CreateComponent<Particle>();
	particle->SetTextureKey(imageKey);

	if (m_isCollide)
	{
		CircleCollider* collider = obj->CreateComponent<CircleCollider>();
		collider->SetRadius(5.f);
		collider->SetRadius(true);
	}

	m_container.push_back(obj);
	m_typeCount++;
}

void ParticleSystem::Generate()
{
	m_count++;

	//파티클 값 설정
	Vector2 pos;
	Vector2 direction;

	switch (m_shape)
	{
	case EMISSION_SHAPE::SQUARE:
		SetSquarePosNDir(pos, direction);
		break;

	case EMISSION_SHAPE::CIRCLE:
		SetCirclePosNDir(pos, direction);
		break;

	case EMISSION_SHAPE::CONE:
		SetConePosNDir(pos, direction);
		break;
	}

	float scale = 0, scaleVar = 0;
	setRandomValue(m_initScale, scale);
	setRandomValue(m_scaleVariance, scaleVar);

	float speed = 0, speedVar = 0;
	setRandomValue(m_initSpeed, speed);
	setRandomValue(m_speedVariance, speedVar);

	float rotation = 0, rotationVar = 0;
	setRandomValue(m_initRotation, rotation);
	setRandomValue(m_rotationVariance, rotationVar);

	float lifeTime = 0;
	setRandomValue(m_lifeTime, lifeTime);

	float alpha = 0, alphaVar = 0;
	setRandomValue(m_initAlpha, alpha);
	setRandomValue(m_AlphaVariance, alphaVar);

	UINT index = 0;

	if (m_typeCount == 1)
	{
		index = 0;
	}
	else
	{
		std::uniform_int_distribution<int> dis(0, m_typeCount - 1);
		index = dis(gen);
	}

	//파티클 생성
	GameObject* obj = new GameObject(*m_container[index]);

	Particle* p = obj->GetComponent<Particle>();
	p->Setup(this
		, pos, scale, rotation, speed, direction
		, m_gravity, lifeTime, speedVar, scaleVar, rotationVar
		, alpha, alphaVar);

	if (m_subEmit)
	{
		p->SetSubEmit(m_subEmitTrigger, m_subEmitTime);
	}

	//씬에 등록
	GetSceneManager()->RegisterObject(obj, 0);

	p->Play();
}

void ParticleSystem::Remove()
{
	m_count--;
}

void ParticleSystem::SubEmit(GameObject* particle)
{
	//파티클 생성
	GameObject* obj = new GameObject(*particle);
	m_count++;

	Particle* p = obj->GetComponent<Particle>();
	Particle* origin = particle->GetComponent<Particle>();
	Transform* t = particle->GetComponent<Transform>();
	p->Setup(this
		, t->GetPosition(), t->GetScale().x, t->GetRotation(), 0, Vector2(0,0)
		, 0, origin->m_lifeTime * 0.5f, 0, 0, /*p->m_dRotation*/ 0
		, origin->m_alpha, origin->m_dAlpha);

	//씬에 등록
	GetSceneManager()->RegisterObject(obj, 0);

	p->Play();
}

void ParticleSystem::SetSquarePosNDir(Vector2& pos, Vector2& direction)
{
	//위치
	pos.x = LinearRandom(m_centerPos.x - m_halfWidth
		, m_centerPos.x + m_halfWidth);
	
	///임시
	if (m_SQUAREHeightRandom == RANDOM_TYPE::NORMAL)
	{
		pos.y = NormalRandom(m_centerPos.y - m_halfHeight
			, m_centerPos.y + m_halfHeight);
		
	}
	else
	{
		pos.y = LinearRandom(m_centerPos.y - m_halfHeight
			, m_centerPos.y + m_halfHeight);
	}


	//방향
	///사각형의 경우 한번만 계산해두고 가져다 쓰면 된다 나중에 최적화
	float radian = DegToRad(m_rotation);
	direction.x = cos(radian);
	direction.y = sin(radian);
	direction.Normalize();
}

void ParticleSystem::SetCirclePosNDir(Vector2& pos, Vector2& direction)
{
	//각도 -> 방향
	float radian = LinearRandom(0.f, (float)6.28318); //0 ~ 360
	float radius = LinearRandom(0.f, m_radius);

	direction.x = cos(radian);
	direction.y = sin(radian);
	direction.Normalize();

	// 반지름과 각도로 좌표 계산
	pos.x = radius * direction.x + m_centerPos.x;
	pos.y = radius * direction.y + m_centerPos.y;
}

void ParticleSystem::SetConePosNDir(Vector2& pos, Vector2& direction)
{
	//각도 -> 방향
	float radian;
	float radius;
	if (m_maxDegree < m_minDegree)
	{
		radian = LinearRandom(DegToRad(m_maxDegree), DegToRad(m_minDegree + 360)); //0 ~ 360
		radius = LinearRandom(0.f, radius);
	}
	else
	{
		radian = LinearRandom(DegToRad(m_minDegree), DegToRad(m_maxDegree)); //0 ~ 360
		radius = LinearRandom(0.f, radius);
	}


	direction.x = cos(radian);
	direction.y = sin(radian);
	direction.Normalize();

	// 반지름과 각도로 좌표 계산
	pos.x = radius * direction.x + m_centerPos.x;
	pos.y = radius * direction.y + m_centerPos.y;
}

void ParticleSystem::setRandomValue(const ParticleValue& value, float& result)
{
	switch (value.randomType)
	{
	case RANDOM_TYPE::NONE:
		result = value.mininum;
		break;

	case RANDOM_TYPE::LINEAR:
		result = LinearRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::NORMAL:
		result = NormalRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::DISCRETE:
		//미구현
		break;
	}
}

void ParticleSystem::setRandomValue(const VarianceValue& value, float& result)
{
	switch (value.randomType)
	{
	case RANDOM_TYPE::NONE:
		result = value.mininum;
		break;

	case RANDOM_TYPE::LINEAR:
		result = LinearRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::NORMAL:
		result = NormalRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::DISCRETE:
		//미구현
		break;
	}
}



float ParticleSystem::LinearRandom(const float& min, const float& max)
{
	if (min == max) return min;
	//if (min > max) return min;

	//랜덤 분포 설정 
	//느려지면 어디저장해놓고 쓰는걸로)
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

float ParticleSystem::NormalRandom(const float& min, const float& max)
{
	float mean = (min + max) / 2;
	float sigma = (max - min) / (2 * 1);
	std::normal_distribution<float> dis(mean, sigma);

	return dis(gen);
}

// float ParticleSystem::DiscreteRandom()
// {
// 	return 0.0f;
// }