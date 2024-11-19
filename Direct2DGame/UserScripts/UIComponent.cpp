#include "UserScriptsPCH.h"
#include "UIComponent.h"


UIComponent::UIComponent()
	:MonoBehaviour(typeid(this).name())
	, m_mouseEvent(nullptr)
	, m_textureRenderer(nullptr)
	, m_mySceneManager(nullptr)
	, isSwitchOn(false)
	, fadeAlpha(0.f)
	, m_deltaTime(0.f)
	, m_myCameraManager(nullptr)
	, m_myInputManager(nullptr)
	, m_transform(nullptr)
	, m_animator(nullptr)
{

}

UIComponent::~UIComponent()
{

}

Component* UIComponent::Clone()
{
	UIComponent* clone = new UIComponent();

	return clone;
}

void UIComponent::Start()
{
	m_mouseEvent = GetComponent<MouseEvent>();
	m_textureRenderer = GetComponent<TextureRenderer>();
	m_transform = GetComponent<Transform>();
	m_animator = GetComponent<Animator>();

	// 매니저
	m_myInputManager = GetInputManager();
	m_mySceneManager = GetSceneManager();
	m_myObjectName = this->GetGameObject()->GetName();
	m_myCameraManager = GetCameraManager();

	fadeAlpha = 1.f;

	if(SoundManager::GetInstance()->isPlayingBGM()==false)
	{
		SoundManager::GetInstance()->PlayBackgroundSound(L"bgm2"); //사운드 넣기
		SoundManager::GetInstance()->SetBGMVolume(0.3f);
	}

}

void UIComponent::Update(float _deltaTime)
{
	m_deltaTime = _deltaTime;

	m_scene = m_mySceneManager->GetCurrentScene();

	if (m_myObjectName == "backToMainButton")
	{
		m_textureRenderer->SetKey(L"back");
		if (m_mouseEvent->IsMouseOn())
		{
			m_textureRenderer->SetKey(L"back");
			m_textureRenderer->SetScale(Vector2(0.07f, 0.07f));
		}
		else
		{
			m_textureRenderer->SetScale(Vector2(0.1f, 0.1f));
		}

		if (m_myInputManager->IsKeyState(KEY::ESC, KEY_STATE::TAP))
		{
			m_mySceneManager->RegisterNextScene(L"MainScene");
		}
	}
	else if(m_myObjectName == "gameStartButton")
	{
		// 마우스 올리면 텍스쳐 변경
		if (m_mouseEvent->IsMouseOn())
		{
			m_animator->Play(gameStartOnMouse, true);
			m_textureRenderer->SetScale(Vector2(0.f, 0.f));
		}
		else
		{
			m_animator->Play(L"x", true);
			m_textureRenderer->SetKey(L"gameStart");
			m_textureRenderer->SetScale(Vector2(1.f, 1.f));

		}

		/*if (m_mouseEvent->IsLBtnDown())
		{
			m_textureRenderer->SetScale(Vector2(0.9f, 0.9f));
		}
		else
		{
			m_textureRenderer->SetScale(Vector2(1.f, 1.f));
		}*/
	}
	else if (m_myObjectName == "crew")
	{
		// 마우스 올리면 텍스쳐 변경
		if (m_mouseEvent->IsMouseOn())
		{
			m_animator->Play(crewOnMouse, true);
			m_textureRenderer->SetScale(Vector2(0.f, 0.f));
		}
		else
		{
			m_animator->Play(L"x", true);
			m_textureRenderer->SetKey(L"crew");
			m_textureRenderer->SetScale(Vector2(1.f, 1.f));
		}

		/*if (m_mouseEvent->IsLBtnDown())
		{
			m_textureRenderer->SetScale(Vector2(0.9f, 0.9f));
		}
		else
		{
			m_textureRenderer->SetScale(Vector2(1.f, 1.f));
		}*/
	}
	else if (m_myObjectName == "gameExit")
	{
		// 마우스 올리면 텍스쳐 변경
		if (m_mouseEvent->IsMouseOn())
		{
			m_animator->Play(gameExitOnMouse, true);
			m_textureRenderer->SetScale(Vector2(0.f, 0.f));
		}
		else
		{
			m_animator->Play(L"x", true);
			m_textureRenderer->SetKey(L"gameExit");
			m_textureRenderer->SetScale(Vector2(1.f, 1.f));
		}

		/*	if (m_mouseEvent->IsLBtnDown())
			{
				m_textureRenderer->SetScale(Vector2(0.9f, 0.9f));
			}
			else
			{
				m_textureRenderer->SetScale(Vector2(1.f, 1.f));
			}*/
	}

	if (isSwitchOn)
	{
		UIFadeOut(m_myObjectName);
	}
}

void UIComponent::Render(D2DRenderer* _d2DRenderer)
{

}

void UIComponent::PostRender(D2DRenderer* _d2DRenderer)
{

}

void UIComponent::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void UIComponent::OnMouse()
{

}

void UIComponent::OnMouseClicked()
{
	if (SoundManager::GetInstance()->isPlayingChannel(10) == false)
		SoundManager::GetInstance()->PlaySFXSound(L"uiButton", 1,10); //사운드 넣기
	if (m_myObjectName == "gameStartButton")
	{
		m_mySceneManager->RegisterNextScene(L"StartCutScene");
		m_myCameraManager->FadeInCamera(1.f, true, ColorF::Black); // 씬 들어갈 때 페이드 인

	}
	else if (m_myObjectName == "crew")
	{
		isSwitchOn = true;
		
		m_myCameraManager->FadeOutCamera(1.f, true, ColorF::Black);

		//m_mySceneManager->RegisterNextScene(L"CrewScene");
	}
	else if (m_myObjectName == "gameExit")
	{
		isSwitchOn = true;
		m_myCameraManager->FadeOutCamera(1.f, true, ColorF::Black);


		//m_mySceneManager->EndGame();
	}	
	else if (m_myObjectName == "backToMainButton")
	{
		isSwitchOn = true;
		m_myCameraManager->FadeOutCamera(1.f, true, ColorF::Black);


		//m_mySceneManager->EndGame();
	}
}

void UIComponent::UIFadeOut(string m_myObjectName)
{
	//m_textureRenderer->SetAlpha(fadeAlpha);

	fadeAlpha -= 1.f * m_deltaTime;
	if (fadeAlpha < 0)
	{
		isSwitchOn = false;
		if(m_myObjectName=="crew")
			m_mySceneManager->RegisterNextScene(L"CrewScene");
		else if(m_myObjectName == "gameExit")
			m_mySceneManager->EndGame();
		else if(m_myObjectName == "backToMainButton")
			m_mySceneManager->RegisterNextScene(L"MainScene");

		m_myCameraManager->FadeInCamera(1.f, true, ColorF::Black);
	}
	
}
