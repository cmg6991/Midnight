#include "UserScriptsPCH.h"
#include "StandLight.h"
#include "StandLightFootSwitch.h"

StandLight::StandLight()
	:MonoBehaviour(typeid(this).name())
	, m_isSwitchOn(false)
	, m_chandlierSwich(nullptr)
	, m_lightObject(nullptr)
	, m_footSwitch(nullptr)
{

}

StandLight::~StandLight()
{

}

Component* StandLight::Clone()
{
	StandLight* clone = new StandLight();
	return clone;
}

void StandLight::Start()
{
	if (m_footSwitch == nullptr)
	{
		// 가장 가까운 샹들리에 찾기 

		const vector<GameObject*>& vec = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::TILE);

		float minimumDistance = FloatMax();
		Vector2 switchPos = GetComponent<Transform>()->GetPosition();

		// 가장 가까울 샹들리에 찾기
		for (auto& object : vec)
		{
			if (object->GetName() == "standLightFootSwitch")
			{
				Vector2 pos = object->GetComponent<Transform>()->GetPosition();

				float distance = (switchPos - pos).Length();
				if (minimumDistance >= distance)
				{
					minimumDistance = distance;
					m_footSwitch = object;
				}
			}
		}
	}

	m_lightObject = GetGameObject()->GetChild("light");
	m_chandlierSwich = GetGameObject()->GetChild("light")->GetChild("chandlierSwitch");
	
}

void StandLight::Update(float _deltaTime)
{
// 	if (m_isSwitchOn)
// 	{
// 		m_lightObject->GetComponent<TextureRenderer>()->SetAlpha(0.5f);
// 		m_chandlierSwich->GetComponent<TextureRenderer>()->SetAlpha(1.f);
// 
// 	}
// 	else
// 	{
// 		m_lightObject->GetComponent<TextureRenderer>()->SetAlpha(0.0f);
// 		m_chandlierSwich->GetComponent<TextureRenderer>()->SetAlpha(0.f);
// 	}

	if (m_footSwitch->GetComponent<StandLightFootSwitch>()->GetFootSwitchOn())
	{
		m_lightObject->GetComponent<TextureRenderer>()->SetAlpha(0.5f);
		if (m_chandlierSwich)
			m_chandlierSwich->GetComponent<TextureRenderer>()->SetAlpha(1.f);
		m_lightObject->GetComponent<BoxCollider>()->SetScale(Vector2(100.f, 200.f));
		m_lightObject->GetComponent<BoxCollider>()->SetOffset(Vector2(0.f, 0.f));
	}
	else
	{
		m_lightObject->GetComponent<TextureRenderer>()->SetAlpha(0.0f);
		if (m_chandlierSwich)
			m_chandlierSwich->GetComponent<TextureRenderer>()->SetAlpha(0.f);
		m_lightObject->GetComponent<BoxCollider>()->SetScale(Vector2(10.f, 0.f));
		m_lightObject->GetComponent<BoxCollider>()->SetOffset(Vector2(0.f, 100.f));

	}



}

void StandLight::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 pos = GetComponent<Transform>()->GetPosition();
	string name = m_footSwitch->GetDebugName();

	pos.y += 50.f;

	wstring nameW;

	nameW.assign(name.begin(), name.end());

	wstring info = L"연결된 스위치 : " + nameW;
	_d2DRenderer->DrawTextW(info, pos, Vector2(pos.x + 200.f, pos.y), D2D1::ColorF::DeepPink);
}

void StandLight::OnCollisionExit(const Collision& _collision)
{
// 	if (_collision.otherObject->GetName() == "player")
// 	{
// 		m_isSwitchOn = false;
// 		m_lightObject->GetComponent<BoxCollider>()->SetScale(Vector2(10.f, 0.f));
// 		m_lightObject->GetComponent<BoxCollider>()->SetOffset(Vector2(0.f, 100.f));
// 	}
}

void StandLight::OnCollisionEnter(const Collision& _collision)
{
// 	if (_collision.otherObject->GetName() == "player")
// 	{
// 		m_isSwitchOn = true;
// 		//m_lightObject->CreateComponent<BoxCollider>();
// 		m_lightObject->GetComponent<BoxCollider>()->SetScale(Vector2(100.f, 200.f));
// 		m_lightObject->GetComponent<BoxCollider>()->SetOffset(Vector2(0.f, 0.f));
// 	}
}
