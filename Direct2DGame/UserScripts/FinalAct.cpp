#include "UserScriptsPCH.h"
#include "FinalAct.h"

FinalAct::FinalAct()
	:MonoBehaviour(typeid(this).name())
	, m_isStart(false)
	,m_index(0)
	,m_ratio(1.f)
{
}

FinalAct::~FinalAct()
{
}

Component* FinalAct::Clone()
{
	return nullptr;
}

void FinalAct::Update(float _deltaTime)
{
	int order = GetDirectManager()->GetCurrentActingOrder();

	if (order == 12)
	{
		m_isStart = true;


	}

	const InputManager* input = GetInputManager();
	if (m_isStart)
	{
		if (input->IsKeyState(KEY::SPACE, KEY_STATE::TAP) || input->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP))
		{
			if (m_index < 2)
				m_index++;
			else
			{
				GetSceneManager()->RegisterNextScene(L"CrewScene");
			}

		}
	}


}

void FinalAct::Render(D2DRenderer* _d2DRenderer)
{

	if (m_isStart)
	{
		if (m_index == 0)
		{
			_d2DRenderer->DrawBitmap(L"S5_01", Vector2::Zero);
		}
		else if (m_index == 1)
		{
			_d2DRenderer->DrawBitmap(L"S5_02", Vector2::Zero);
		}
		else if (m_index == 2)
		{
			_d2DRenderer->DrawBitmap(L"S5_03", Vector2::Zero);
		}
	}

}

void FinalAct::OnMouseClicked()
{

}

