#include "GameProcessPCH.h"
#include "SceneChangeButton.h"
#include "SceneManager.h"

SceneChangeButton::SceneChangeButton()
	:MonoBehaviour(typeid(this).name())
	,m_chageScneName()
{

}

SceneChangeButton::~SceneChangeButton()
{

}

Component* SceneChangeButton::Clone()
{
	SceneChangeButton* clone = new SceneChangeButton();
	clone->m_chageScneName = m_chageScneName;


	return clone;
}

void SceneChangeButton::OnMouseClicked()
{
	GetSceneManager()->RegisterNextScene(m_chageScneName);
}
