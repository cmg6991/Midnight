#include "UserScriptsPCH.h"
#include "Thread.h"
#include "Button.h"

Thread::Thread()
	:MonoBehaviour(typeid(this).name())
	, m_button(nullptr)
	, m_alpha(0.f)
	//, m_buttonConmponent(nullptr)
	, m_textureRenderer(nullptr)
	, m_deltaTime(0.f)
	, m_isSwitchOn(false)
{

}

Thread::~Thread()
{

}

Component* Thread::Clone()
{
	Thread* clone = new Thread();

	return clone;
}

void Thread::Start()
{
	m_textureRenderer = GetComponent<TextureRenderer>();

/*	m_buttonConmponent = m_button->GetComponent<Button>();*/
	m_alpha = 1.f;
}

void Thread::Update(float _deltaTime)
{
	m_deltaTime = _deltaTime;
	if (m_isSwitchOn)
	{
		m_alpha -= 1.f * m_deltaTime;
		m_textureRenderer->SetAlpha(m_alpha);
	}
	if (m_alpha < 0)
	{
		// 파괴
		this->GetGameObject()->Destory();

	}
}

void Thread::Render(D2DRenderer* _d2DRenderer)
{

}

void Thread::PostRender(D2DRenderer* _d2DRenderer)
{

}

void Thread::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void Thread::OnCollisionEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		m_isSwitchOn = true;
		if (SoundManager::GetInstance()->isPlayingChannel(13) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"cutThread", 1, 13); //사운드 넣기
	}

	
}
