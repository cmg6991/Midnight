#include "UserScriptsPCH.h"
#include "SoundMaker.h"
#include "Chaser.h"

SoundMaker::SoundMaker()
	:m_chaser(nullptr), m_thisPosition(), m_isPlaySound(false)
{
}

SoundMaker::~SoundMaker()
{
}

void SoundMaker::Start()
{
	if (m_chaser)
	{
		return;
	}

	m_thisPosition = GetComponent<Transform>()->GetPosition();
}

void SoundMaker::Update(float _deltaTime)
{
	// 가장 가까운 하녀 찾기
	const vector<GameObject*>& chasers = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::CHASER);

	GameObject* closeMaid = nullptr;
	float minimumDistance = FloatMax();

	for (auto chaser : chasers)
	{
		if (chaser->GetComponent<Chaser>() == nullptr)
			continue;

		Vector2 position = chaser->GetComponent<Transform>()->GetPosition();

		if (abs(m_thisPosition.y - position.y) > 150)
			continue;

		float distance = (m_thisPosition - position).Length();
		if (distance <= minimumDistance)
		{
			minimumDistance = distance;
			m_chaser = chaser->GetComponent<Chaser>();
		}
	}

	assert(m_chaser || !L"하녀를 한명이라도 추가해주세요");

}

void SoundMaker::OnTriggerEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() != OBJECT_TYPE::PLAYER)
		return;

	if (m_chaser != nullptr)
		m_chaser->ObjectSuspictionCallback(GetGameObject());


 
	///소리 재생

	if (GetGameObject()->GetName() == "leafDummy")
	{
		if (SoundManager::GetInstance()->isPlayingChannel(8) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"leaf", 1, 8); //사운드 넣기
	}
	else
		if (SoundManager::GetInstance()->isPlayingChannel(2) == false)
	{
			SoundManager::GetInstance()->PlaySFXSound(L"cushion", 1, 2); //사운드 넣기
	}

}


void SoundMaker::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 pos = GetComponent<Transform>()->GetPosition();

	if (m_chaser == nullptr)
		return;


	string name = m_chaser->GetGameObject()->GetDebugName();

	pos.y += 50.f;

	wstring nameW;

	nameW.assign(name.begin(), name.end());

	wstring info = L"연결된 오브젝트 : " + nameW;
	_d2DRenderer->DrawTextW(info, pos, Vector2(pos.x + 200.f, pos.y), D2D1::ColorF::DeepPink);
}
