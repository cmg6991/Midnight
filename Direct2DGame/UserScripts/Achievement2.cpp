#include "UserScriptsPCH.h"
#include "Achievement2.h"
#include "Candle.h"

Achievement2::Achievement2()
	:MonoBehaviour(typeid(this).name()), m_transform(nullptr)
	, m_input(nullptr), m_isOpen(false), m_showDuration(3.f), m_showTimer(0.f)
{

}

Achievement2::~Achievement2()
{ }

/// 맴버 함수로 쓰는 방법을 모르겠어서 무지성전역으로 박았음,
// x좌표 기준으로 정렬 
bool SortbyX(Candle* chan1, Candle* chan2)
{
	if (chan1->GetGameObject()->GetComponent<Transform>()->GetPosition().x
		< chan2->GetGameObject()->GetComponent<Transform>()->GetPosition().x)
		return true;
	else
		return false;
}

void Achievement2::Start()
{
	m_input = GetInputManager();
	m_transform = GetComponent<Transform>();
	m_isOn = { false, false, false, false , false, false };

	// 모든 샹들리에 찾기
	const vector<GameObject*>& objs = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::INTERACTIVE_ITEM);
	for (auto obj : objs)
	{
		if (obj->GetComponent<Candle>() != nullptr)
			m_candles.push_back(obj->GetComponent<Candle>());
	}

	// x 기준으로 정렬
	std::sort(m_candles.begin(), m_candles.end(), SortbyX);
}

void Achievement2::Update(float _deltaTime)
{
	// 반복 돌면서 켜졌는지 확인
	m_Count = 0;
	for (int i = 0; i < m_candles.size(); i++)
	{
		if (m_candles[i]->IsLightOn())
		{
			m_isOn[i] = true;
			m_Count++;
		}
	}

	// 이전 프레임이랑 달라졌다면 보임
	if (m_Count != m_lastCount)
	{
		m_isOpen = true;
		m_showTimer = m_showDuration;
	}
	m_lastCount = m_Count;

	// 키 입력시 보임
	if (m_input->GetKeyState(KEY::Q) == KEY_STATE::HOLD)
	{
		m_isOpen = true;
		m_showTimer = m_showDuration;
	}

	// 시간이 지나면 닫힘 (위 : 580, 아래 : 505)
	if (0 < m_showTimer)
	{
		m_showTimer -= _deltaTime;
		if (m_showTimer < 0)
		{
			m_showTimer = 0;
			m_isOpen = false;
		}

		float y = m_transform->GetPosition().y;
		y = FMath::Lerp(y, 505, _deltaTime * 5);
		m_transform->SetPosition(Vector2(0.f, y));
	}
	else
	{
		float y = m_transform->GetPosition().y;
		y = FMath::Lerp(y, 580, _deltaTime * 5);
		m_transform->SetPosition(Vector2(0.f, y));
	}
}

void Achievement2::Render(D2DRenderer* _d2DRenderer)
{
	// 배경 랜더
	Vector2 pos = m_transform->GetPosition();
	_d2DRenderer->DrawBitmap(L"진행도창", pos);

	// 아이콘 랜더
	pos.x -= 65 * (m_isOn.size() - 1) * 0.5;
	for (auto obj : m_isOn)
	{
		if (obj == true)
		{
			_d2DRenderer->DrawBitmap(L"촛불 활성", pos);
		}
		else
		{
			_d2DRenderer->DrawBitmap(L"촛불 비활성", pos);
		}
		pos.x += 65;
	}
}
