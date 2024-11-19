#include "GameProcessPCH.h"
#include "PlayButton.h"
#include "GameObject.h"
#include "PopupWindow.h"
#include "Transform.h"


PlayButton::PlayButton()
	:MonoBehaviour(typeid(this).name())
	,m_popupWindow(nullptr)
{

}

PlayButton::~PlayButton()
{

}

Component* PlayButton::Clone()
{
	// 복사하지 않음
	assert(nullptr);

	return nullptr;
}

void PlayButton::Start()
{
	m_popupWindow = GetComponent<Transform>()->GetParent()->GetComponent<PopupWindow>();

	// 부모의 컴포넌트에 popupWindow가 없는경우
	assert(m_popupWindow);


}

void PlayButton::OnMouseClicked()
{
	m_popupWindow->SetActive(false);

}
