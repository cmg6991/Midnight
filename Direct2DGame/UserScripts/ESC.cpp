#include "UserScriptsPCH.h"
#include "ESC.h"

ESC::ESC()
	:MonoBehaviour(typeid(this).name())
	,isSwitchOn(false)
	, fadeAlpha(0.f)
	, m_deltaTime(0.f)
{

}

ESC::~ESC()
{

}

void ESC::Start()
{
	m_myObjectName = this->GetGameObject()->GetName();
	fadeAlpha = 1.f;
}

void ESC::Update(float _deltaTime)
{
	m_deltaTime = _deltaTime;

	const InputManager* input = GetManagerSet()->GetInputManager();

	if (input->IsKeyState(KEY::ESC, KEY_STATE::TAP))
	{
		isSwitchOn = true;
		GetManagerSet()->GetCameraManager()->FadeOutCamera(1.f, true, ColorF::Black);
	}
	if (isSwitchOn)
	{
		UIFadeOut(m_myObjectName);
	}

}

void ESC::OnMouseClicked()
{
	if (m_myObjectName == "EscButton")
	{
		isSwitchOn = true;
		GetManagerSet()->GetCameraManager()->FadeOutCamera(1.f, true, ColorF::Black);
	}
}

void ESC::UIFadeOut(string m_myObjectName)
{
	fadeAlpha -= 1.f * m_deltaTime;
	if (fadeAlpha < 0)
	{
		isSwitchOn = false;
		if (m_myObjectName == "EscButton")
			GetManagerSet()->GetSceneManager()->RegisterNextScene(L"MainScene");
		else if(m_myObjectName =="ESC")
			GetManagerSet()->GetSceneManager()->RegisterNextScene(L"MainScene");


		GetManagerSet()->GetCameraManager()->FadeInCamera(1.f, true, ColorF::Black);
	}
}

