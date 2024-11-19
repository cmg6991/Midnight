#include "UserScriptsPCH.h"
#include "Feather.h"

Feather::Feather()
	:MonoBehaviour(typeid(this).name())
	, m_rigidBody(nullptr)
	, m_waitTime(0.f)
	, m_isStepOn(false)
	, m_deltaTime(0.f)
	, m_alpha(0.f)
	, m_textureRenderer(nullptr)
	, m_isFadeOut(false)
	, m_transform(nullptr)
	, m_isRecreate(false)
	, m_wait2Second(0.f)
	, m_particleSystem(nullptr)
{

}

Feather::~Feather()
{

}

Component* Feather::Clone()
{
	Feather* clone = new Feather();
	return clone;
}

void Feather::Start()
{
	m_rigidBody = GetComponent<RigidBody>();
	m_textureRenderer = GetComponent<TextureRenderer>();
	//m_transform = GetComponent<Transform>();
	m_particleSystem = GetComponent<ParticleSystem>();

	m_waitTime = 1.f;
	m_wait2Second = 2.f;
	m_rigidBody->SetFixed(true);
	m_alpha = 1.f;
	//m_featherPosition =m_transform->GetPosition(); // 초기에 설정된 포지션을 저장, 깃털을 리스폰할 때 여기로 이동
}


void Feather::Update(float _deltaTime)
{
	m_deltaTime = _deltaTime;

	if (m_isStepOn)
	{
		Wait();
	}
	if (m_isFadeOut)
	{
		
		Wait2Second();
	}
	if (m_isRecreate)
	{
		MakeFeather();
	}
}

void Feather::Render(D2DRenderer* _d2DRenderer)
{

}

void Feather::PostRender(D2DRenderer* _d2DRenderer)
{

}

void Feather::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void Feather::OnCollisionEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		m_isStepOn = true;
		m_isRecreate = false;
	}
}


void Feather::Wait()
{
	m_waitTime -= 1.f * m_deltaTime;
	if (m_waitTime < 0)
	{
		if (m_rigidBody != nullptr) 
		{
			m_rigidBody->~RigidBody();
			m_rigidBody = nullptr;
			m_particleSystem->Play();
			if (SoundManager::GetInstance()->isPlayingChannel(4) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"feather", 1,4); //사운드 넣기
		}
		m_isFadeOut = true;
		m_alpha -= 2.f * m_deltaTime;
		m_textureRenderer->SetAlpha(m_alpha);
	}
}

void Feather::Wait2Second()
{
	m_wait2Second -= 1.f * m_deltaTime;

	if (m_wait2Second < 0)
	{
		m_isRecreate = true;
	}
}

void Feather::MakeFeather()
{
	if (m_alpha < 1.f)
	{
		m_alpha += 2.f * m_deltaTime;
		m_textureRenderer->SetAlpha(m_alpha);
	}

	if (m_rigidBody == nullptr)
	{
		m_rigidBody = CreateComponent<RigidBody>();
		m_rigidBody->SetMass(100.f);
		m_rigidBody->SetFixed(true);
		m_waitTime = 1.f;
		m_wait2Second = 2.f;
		m_isFadeOut = false;
		m_isStepOn = false;
		m_alpha = 0.f;
	}
}

