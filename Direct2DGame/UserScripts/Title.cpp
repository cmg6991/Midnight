#include "UserScriptsPCH.h"
#include "Title.h"

Title::Title()
	:MonoBehaviour(typeid(this).name())
	,m_time(0.f), m_timer(0.f), m_currentIndex(0), m_ani(nullptr)
{

}

Title::~Title()
{

}

void Title::Start()
{
	const float oneframe = 1.f / 72.f;
	m_ani = GetComponent<Animator>();
	
	m_ani->CreateAnimation2(L"0", L"타이틀1_1920x800", Vector2::Zero
		, Vector2(1920, 800), Vector2(1920, 0), oneframe, 72, FLIP_TYPE::NONE, Vector2(0, 800), 8);
	m_ani->CreateAnimation2(L"1", L"타이틀2_1920x800", Vector2::Zero
		, Vector2(1920, 800), Vector2(1920, 0), oneframe, 72, FLIP_TYPE::NONE, Vector2(0, 800), 8);
	m_ani->CreateAnimation2(L"2", L"타이틀3_1920x800", Vector2::Zero
		, Vector2(1920, 800), Vector2(1920, 0), oneframe, 72, FLIP_TYPE::NONE, Vector2(0, 800), 8);
	m_ani->CreateAnimation2(L"3", L"타이틀4_1920x800", Vector2::Zero
		, Vector2(1920, 800), Vector2(1920, 0), oneframe, 72, FLIP_TYPE::NONE, Vector2(0, 800), 8);

	m_ani->Play(L"1", true);
	m_time = 71.95f / 60.f;
}

void Title::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (m_timer > 1.f)
	{
		m_timer -= 1.f;
		m_currentIndex = (m_currentIndex + 1) % 4;

		m_ani->Reset();
	}

	switch (m_currentIndex)
	{
	case 0:
		m_ani->Play(L"0", true);
		break;
	
	case 1:
		m_ani->Play(L"1", true);
		break;

	case 2:
		m_ani->Play(L"2", true);
		break;

	case 3:
		m_ani->Play(L"3", true);
		break;
	}
}
