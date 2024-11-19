#include "UserScriptsPCH.h"
#include "Candle.h"
#include "ClearCheck.h"

Candle::Candle()
	:MonoBehaviour(typeid(this).name())
	, m_pointLight(nullptr), m_lightCollider(nullptr), m_inputManager(nullptr)
	, m_isLightOn(false), m_isWorkingDone(false)
	, gen(rd()), dis(0.2f ,2.f), m_timer(0),m_changeTime(0), m_isGoingLighter(-1)
{

}

Candle::~Candle()
{

}

void Candle::Start()
{
	m_pointLight = GetComponent<PointLightRenderer>();
	m_lightCollider = GetComponent<CircleCollider>();
	m_inputManager = GetManagerSet()->GetInputManager();

	m_pointLight->SetIntensity(0);
	m_pointLight->SetRGB(0xff9d4f);
	m_pointLight->SetScale(Vector2(2.f,2.f));
	//m_pointLight->SetRGB(Vector3F(0.f, 0.f, 1.f));

	m_lightTexture = GetGameObject()->GetChild("candleLight")->GetComponent<TextureRenderer>();
}

void Candle::Update(float _deltaTime)
{
	if (m_isLightOn)
	{
		//ºÒºû
		if (!m_isWorkingDone)
		{
			float intensity = m_pointLight->GetIntensity();
			intensity = FMath::Lerp(intensity, 6, _deltaTime);
			m_pointLight->SetIntensity(intensity);
			
			float alpha = m_lightTexture->GetAlpha();
			alpha = FMath::Lerp(alpha, 0.8, _deltaTime);
			m_lightTexture->SetAlpha(alpha);

			if (5 < intensity)
			{
				m_isWorkingDone = true;
				m_lightTexture->SetAlpha(0.8f);
			}
		}


		//ÄÝ¶óÀÌ´õ
		float radius = m_lightCollider->GetRadius();
		radius = FMath::Lerp(radius, 1000, _deltaTime * 0.7);
		m_lightCollider->SetRadius(radius);
	
		//ºÒºû ±ôºýÀÌ±â
		if (m_isWorkingDone)
		{
			if (m_isGoingLighter == -1)
			{
				float intensity = m_pointLight->GetIntensity();
				intensity = FMath::Lerp(5, 3.5, m_timer / m_changeTime);
				m_pointLight->SetIntensity(intensity);
			}
			else
			{
				float intensity = m_pointLight->GetIntensity();
				intensity = FMath::Lerp(3.5, 5, m_timer / m_changeTime);
				m_pointLight->SetIntensity(intensity);
			}
			
			m_timer += _deltaTime;
			if (m_changeTime < m_timer)
			{
				m_isGoingLighter *= -1;
				m_timer -= m_changeTime;
				m_changeTime = dis(gen);
			}
		}
	}
}

void Candle::OnTriggerStay(const Collision& _collision)
{

	// ÃÐºÒÄÑ±â
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER 
		&& m_inputManager->GetKeyState(KEY::E) == KEY_STATE::TAP
		&& !m_isLightOn )
	{
		if (SoundManager::GetInstance()->isPlayingChannel(0) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"candle", 1,0); //»ç¿îµå ³Ö±â
		LightCandle();

		m_clearCheck->GetComponent<ClearCheck>()->AddClearIndex();

		GetGameObject()->GetChild("particleSpawner")->GetComponent<ParticleSystem>()->Stop();
	}
}

void Candle::DebugRender(D2DRenderer* _d2DRenderer)
{
// 	std::wstringstream wss;
// 	wss << m_pointLight->GetIntensity();
// 	wstring c = L"¹à±â: ";
// 	c += wss.str();
// 	_d2DRenderer->DrawTextW(c, Vector2(700,-100)
// 		, Vector2(700,-100) + Vector2(300, 0));
}

void Candle::LightCandle()
{
	m_isLightOn = true;
	GetComponent<TextureRenderer>()->SetKey(L"13");
	GetComponent<ParticleSystem>()->Play();
	m_changeTime = dis(gen);
}
