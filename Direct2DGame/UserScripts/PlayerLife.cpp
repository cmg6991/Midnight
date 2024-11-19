#include "UserScriptsPCH.h"
#include "PlayerLife.h"

PlayerLife::PlayerLife()
	:MonoBehaviour(typeid(this).name())
	,m_remainLife(3)
	,m_particle(nullptr)
{

}

PlayerLife::~PlayerLife()
{

}

void PlayerLife::Start()
{
	m_particle = CreateComponent<ParticleSystem>();
	m_particle->AddDefaultParticle(L"부스러기1"); m_particle->GetParticlePrefab(0)->SetObjectType(OBJECT_TYPE::BACK_UI);
	m_particle->AddDefaultParticle(L"부스러기2"); m_particle->GetParticlePrefab(1)->SetObjectType(OBJECT_TYPE::BACK_UI);
	m_particle->AddDefaultParticle(L"부스러기3"); m_particle->GetParticlePrefab(2)->SetObjectType(OBJECT_TYPE::BACK_UI);

	m_particle->m_isRepeat = false;
	m_particle->m_radius = 60.f;
	m_particle->m_duration = 0.002f;
	m_particle->m_emitInterval = 0.00005f;
	m_particle->m_initRotation = { 0.f,360.f,RANDOM_TYPE::LINEAR };
	m_particle->m_initScale = { 1.f,1.5f,RANDOM_TYPE::LINEAR };
	m_particle->m_initSpeed = 5.f;
	m_particle->m_speedVariance = -5.f;
	m_particle->m_lifeTime = 1.f;
	m_particle->m_AlphaVariance = { -1.5, -1.f, RANDOM_TYPE::LINEAR, VARIANCE_TYPE::VALUE };
	m_particle->m_gravity = 0.3f;
	m_particle->m_maxCount = 7;
	m_particle->m_rotationVariance = { -5, 5, RANDOM_TYPE::LINEAR, VARIANCE_TYPE::VALUE };
}

void PlayerLife::Update(float _deltaTime)
{
	//위치 : 카메라 좌표 + Vector2(875,465)
	Vector2 cameraPos = GetCameraManager()->GetCamera()->GetPosition();
	m_particle->m_offset = cameraPos + Vector2(875, 465);
}

void PlayerLife::Render(D2DRenderer* _d2DRenderer)
{
	_d2DRenderer->SetCameraAffected(false);
	_d2DRenderer->DrawBitmap(m_texture[m_remainLife], Vector2(875, 465));
	_d2DRenderer->SetCameraAffected(true);
}

void PlayerLife::DicreaseLife()
{
	if (1 <= m_remainLife)
	{
		m_remainLife--;
		m_particle->Play();
		if (SoundManager::GetInstance()->isPlayingChannel2(9) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"cookie", 2, 9);
	}
}
