#include "UserScriptsPCH.h"
#include "window.h"
#include "ClearCheck.h"

Window::Window()
	:MonoBehaviour(typeid(this).name())
	, m_myButtonInputManager(nullptr)
	, m_isInputOn(false)
	, m_isSwitchOn(false)
	, m_isOpen(false)
{

}

Window::~Window()
{

}

Component* Window::Clone()
{
	Window* clone = new Window();
	return clone;
}

void Window::Start()
{
	m_boxCollider = GetComponent<BoxCollider>();
	m_textureRenderer = GetComponent<TextureRenderer>();
	m_myButtonInputManager = GetInputManager();
	m_isSwitchOn = false;

}

void Window::Update(float _deltaTime)
{
	if (m_myButtonInputManager->IsKeyState(KEY::E, KEY_STATE::TAP) && m_isInputOn && !m_isOpen)
	{
		m_clearCheck->GetComponent<ClearCheck>()->AddClearIndex();
		if (SoundManager::GetInstance()->isPlayingChannel(1) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"curtain", 1,1); //사운드 넣기
		m_textureRenderer->SetKey(L"windowOpen");
		GetGameObject()->GetChild("particleSpawner")->GetComponent<ParticleSystem>()->Stop();
		m_isOpen = true;
	}
	m_isInputOn = false;
}

void Window::Render(D2DRenderer* _d2DRenderer)
{

}

void Window::PostRender(D2DRenderer* _d2DRenderer)
{

}

void Window::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void Window::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		m_isInputOn = true;
	}
}
