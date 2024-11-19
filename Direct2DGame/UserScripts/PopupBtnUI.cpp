#include "UserScriptsPCH.h"
#include "PopupBtnUI.h"

PopupBtnUI::PopupBtnUI()
	:MonoBehaviour(typeid(this).name())
	,m_aniName()
	,m_animator(nullptr)
	,m_onMouse(false)
{

}

PopupBtnUI::~PopupBtnUI()
{

}

Component* PopupBtnUI::Clone()
{

	return nullptr;
}

void PopupBtnUI::Start()
{
	m_animator = GetComponent<Animator>();
	m_textureRenderer = GetComponent<TextureRenderer>();
}

void PopupBtnUI::OnMouse()
{
	m_onMouse = true;

}

void PopupBtnUI::Update(float _deltaTime)
{

	if (m_onMouse)
	{
		m_animator->SetShow(true);
		m_animator->Play(m_aniName, true);

		m_textureRenderer->SetAlpha(0.f);
	}
	else
	{
		m_animator->SetShow(false);

		m_textureRenderer->SetAlpha(1.f);
	}

	m_onMouse = false;

}

void PopupBtnUI::OnMouseClicked()
{
	if (SoundManager::GetInstance()->isPlayingChannel(10) == false)
		SoundManager::GetInstance()->PlaySFXSound(L"uiButton", 1, 10); //사운드 넣기
}
