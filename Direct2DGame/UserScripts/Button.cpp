#include "UserScriptsPCH.h"
#include "Button.h"

Button::Button()
	:MonoBehaviour(typeid(this).name())
	, m_myButtonInputManager(nullptr)
	, m_isInputOn(false)
	, m_isSwitchOn(false)
{

}

Button::~Button()
{

}

Component* Button::Clone()
{
	Button* clone = new Button();
	return clone;
}

void Button::Start()
{
	
	m_boxCollider = GetComponent<BoxCollider>();
	m_textureRenderer =GetComponent<TextureRenderer>();
	m_isSwitchOn = false;
	m_myButtonInputManager = GetInputManager();
	
}

void Button::Update(float _deltaTime)
{
	
	if (m_myButtonInputManager->IsKeyState(KEY::E, KEY_STATE::TAP) && m_isInputOn)
	{
		SetSwitchOn(true);
	}
	
	m_isInputOn = false;
}

void Button::Render(D2DRenderer* _d2DRenderer)
{

}

void Button::PostRender(D2DRenderer* _d2DRenderer)
{

}

void Button::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void Button::OnCollisionStay(const Collision& _collision)
{
	// 플레이어와 닿아있을 때 키입력 활성화
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		m_isInputOn = true;
	}
}

