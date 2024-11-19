#include "UserScriptsPCH.h"
#include "FreezeEffect.h"
#include "PlayerComponent.h"

FreezeEffect::FreezeEffect()
	:MonoBehaviour(typeid(this).name())
	,m_animator(nullptr)
	,m_defalutJumpPower(0.f)
	,m_defalutPlayerSpeed(0.f)
	,m_elapsedTime(0.f)
	,m_freezeRatio(0.f)
	,m_freezeTime(0.f)
	,m_player(nullptr)
	,m_isFreezing(false)
	,m_particleSystem(nullptr)
{

}

FreezeEffect::~FreezeEffect()
{

}

Component* FreezeEffect::Clone()
{
	// 복사하지 않음
	assert(nullptr);


	return nullptr; 
}

void FreezeEffect::Start()
{
	m_animator = GetComponent<Animator>();
	m_player = GetComponent<PlayerComponent>();
	m_particleSystem = GetComponent<ParticleSystem>();

	m_defalutPlayerSpeed = 300.f;
	m_defalutJumpPower = 600.f;

	m_freezeTime = 3.f;
}

void FreezeEffect::Update(float _deltaTime)
{
	if (!m_isFreezing)
		return;

	m_elapsedTime += _deltaTime;

	m_freezeRatio = m_elapsedTime / m_freezeTime;

	m_player->SetSpeed(m_defalutPlayerSpeed * m_freezeRatio);
	m_player->SetJumpPower( m_defalutJumpPower * m_freezeRatio);
	m_animator->SetEffectRatio(m_freezeRatio);
	m_animator->SetTimeRatio(m_freezeRatio);

	if (m_elapsedTime >= m_freezeTime)
	{
		m_isFreezing = false;
		m_elapsedTime = 0.f;
		m_player->SetJumpPower(m_defalutJumpPower);
		m_player->SetSpeed(m_defalutPlayerSpeed);
		m_player->SetFreeze(false);
		m_animator->SetTimeRatio(1.f);
		m_particleSystem->Stop();

		m_animator->SetEffect(false);
	}


}

void FreezeEffect::Freeze()
{
	// 얼기효과 시작 
	m_elapsedTime = 0.f;
	m_animator->SetEffectRatio(0.f);
	m_isFreezing = true;
	m_freezeRatio = 0.f;
	m_player->SetSpeed(0.f);
	m_animator->SetTimeRatio(0.f);
	m_particleSystem->Play();
	m_animator->SetEffect(true);
}
