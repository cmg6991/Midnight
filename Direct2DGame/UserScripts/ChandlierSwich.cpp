#include "UserScriptsPCH.h"
#include "ChandlierSwich.h"
#include "Chandlier.h"

ChandlierSwich::ChandlierSwich()
	: MonoBehaviour(typeid(this).name())
	, m_isSwitchOn(false)
	, m_textureRenderer(nullptr)
	, m_chandlier(nullptr)
	, m_inputManager(nullptr)
	, m_isLightOn(false)
	, m_isRabbit(false)
	, m_isShow(false)
	, m_psSwitch(nullptr)
{

}

ChandlierSwich::~ChandlierSwich()
{

}

Component* ChandlierSwich::Clone()
{
	ChandlierSwich* clone = new ChandlierSwich();
	return clone;
}

void ChandlierSwich::Start()
{
	m_inputManager = GetInputManager();
	m_textureRenderer = GetComponent<TextureRenderer>();
	m_psSwitch = GetComponent<ParticleSystem>();
	if (!m_chandlier)
	{
		// 가장 가까운 샹들리에 찾기 

		const vector<GameObject*>& vec = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::INTERACTIVE_ITEM);

		float minimumDistance = FloatMax();

	
		if (!m_isShow)
		{
			GameObject* stand = GetComponent<Transform>()->GetParent()->GetComponent<Transform>()->GetParent();
			stand->GetComponent<Transform>()->LateUpdate(0.f);
		}

		Vector2 switchPos = GetComponent<Transform>()->GetPosition();
		

		// 가장 가까울 샹들리에 찾기
		for (auto& object : vec)
		{
			if (object->GetName() == "chandelier")
			{
				Vector2 pos = object->GetComponent<Transform>()->GetPosition();
				
				float distance = (switchPos - pos).Length();

				if (minimumDistance >= distance)
				{
					minimumDistance = distance;
					m_chandlier = object;
				}
			}
		}
	
	}


}

void ChandlierSwich::Update(float _deltaTime)
{
	if (m_isRabbit)
	{
		if (m_inputManager->IsKeyState(KEY::E, KEY_STATE::TAP))
		{
			if (SoundManager::GetInstance()->isPlayingChannel(9) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"switch", 1,9);
			m_chandlier->GetComponent<Chandlier>()->LightOn();
			m_textureRenderer->SetKey(L"샹들리에 스위치on");
			m_psSwitch->Play();
		}
	}

}

void ChandlierSwich::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 pos = GetComponent<Transform>()->GetPosition();
	string name = m_chandlier->GetDebugName();

	pos.y += 50.f;

	wstring nameW;

	nameW.assign(name.begin(), name.end());

	wstring info = L"연결된 샹들리에 : " + nameW;
	_d2DRenderer->DrawTextW(info, pos, Vector2(pos.x + 200.f, pos.y), D2D1::ColorF::DeepPink);
}

void ChandlierSwich::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetName() == "rabbit" && m_isLightOn)
	{
		m_isRabbit = true;
	}

	if (_collision.otherObject->GetName() == "rabbit" && m_isShow)
	{
		m_isRabbit = true;
	}

	if (_collision.otherObject->GetName() == "player" && m_isShow)
	{
		if (m_inputManager->IsKeyState(KEY::E, KEY_STATE::TAP))
		{
			SoundManager::GetInstance()->PlaySFXSound(L"switch", 1,9);
			m_chandlier->GetComponent<Chandlier>()->LightOn();
			m_textureRenderer->SetKey(L"샹들리에 스위치on");
			m_psSwitch->Play();
		}
	}

}

void ChandlierSwich::OnCollisionEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetName() == "light")
		m_isLightOn = true;
}

void ChandlierSwich::OnCollisionExit(const Collision& _collision)
{

	if (_collision.otherObject->GetName() == "light")
	{
		m_isRabbit = false;
		m_isLightOn = false;
	}
	if (_collision.otherObject->GetName() == "rabbit")
	{
		m_isRabbit = false;
	}

}
