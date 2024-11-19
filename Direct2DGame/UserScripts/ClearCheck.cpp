#include "UserScriptsPCH.h"
#include "ClearCheck.h"

ClearCheck::ClearCheck()
	:MonoBehaviour(typeid(this).name())
	,m_isFinished(false)
	,m_clearIndex(0)
	,m_tagetIndex(0)
	,m_sceneName()
	,m_elapsedTime(0.f)
	,m_isShowImage(false)
	,m_cutName()
	,m_clearState(0)
	,m_isShowSpacebar(false)
{

}

ClearCheck::~ClearCheck()
{

}

Component* ClearCheck::Clone()
{
	return nullptr;
}

void ClearCheck::Start()
{
	m_sceneName = GetSceneManager()->GetCurrentScene()->GetSceneName();

}

void ClearCheck::Update(float _deltaTime)
{
	const InputManager* input = GetInputManager();
	
	// 처음 상호작용하고 대사재생
	int order = GetDirectManager()->GetCurrentActingOrder();

	if (m_sceneName == L"Stage1" && order == 7 && m_clearIndex == 1)
	{
		GetDirectManager()->FinishActing(order);
	}

	if (m_sceneName == L"Stage2" && order == 8 && m_clearIndex == 1)
	{
		GetDirectManager()->FinishActing(order);
	}

	if (m_sceneName == L"Stage3" && order == 8 && m_clearIndex == 1)
	{
		GetDirectManager()->FinishActing(order);
	}


	if (m_clearIndex == m_tagetIndex && !m_isFinished)
	{
		//  다음 씬으로 넘어가는 조건을 설정한다. 
		GetDirectManager()->FinishActing(order);
		m_isFinished = true;
	}

	
	// 스테이지 1 클리어 
	if(m_sceneName == L"Stage1" && order == 17 && !m_isClearStage)
	{
		m_isClearStage = true;
		m_isShowImage = true;
	}
	if (m_isClearStage && m_sceneName == L"Stage1")
	{
		m_elapsedTime += _deltaTime;
		switch (m_clearState)
		{
		case 0:
			if (2.f <= m_elapsedTime) m_clearState = 1;
			break;

		case 1:
			m_isShowSpacebar = true;
			if (input->IsKeyState(KEY::SPACE, KEY_STATE::TAP))
			{
				m_clearState = 2;
				m_elapsedTime = 8.f;
			}
			else if (8.f <= m_elapsedTime)
				m_clearState = 2;
			break;

		case 2:
			GetCameraManager()->FadeOutCamera(1.5f,false); // 페이트 아웃
			m_clearState = 3;
			break;

		case 3:
			if (9.4f <= m_elapsedTime)
				m_clearState = 4;
			break;

		case 4:
			GetSceneManager()->RegisterNextScene(L"Stage2");
			break;
		}
	}

	// 스테이지 2 클리어 
	if (m_sceneName == L"Stage2" && order == 20 && !m_isClearStage)
	{
		m_isClearStage = true;
		m_isShowImage = true;
	}
	if (m_isClearStage && m_sceneName == L"Stage2")
	{ 
		m_elapsedTime += _deltaTime;
		switch (m_clearState)
		{
		case 0:
			if (2.f <= m_elapsedTime) m_clearState = 1;
			break;

		case 1:
			m_isShowSpacebar = true;
			if (input->IsKeyState(KEY::SPACE, KEY_STATE::TAP))
			{
				m_clearState = 2;
				m_elapsedTime = 8.f;
			}
			else if (8.f <= m_elapsedTime)
				m_clearState = 2;
			break;

		case 2:
			GetCameraManager()->FadeOutCamera(1.5f, false); // 페이트 아웃
			m_clearState = 3;
			break;

		case 3:
			if (9.4f <= m_elapsedTime)
				m_clearState = 4;
			break;

		case 4:
			GetSceneManager()->RegisterNextScene(L"Stage3");
			break;
		}
	}

	// 스테이지 3 클리어
	if (m_sceneName == L"Stage3" && order == 21&& !m_isClearStage)
	{
		m_isClearStage = true;
		m_isShowImage = true;
	}
	if (m_isClearStage && m_sceneName == L"Stage3")
	{
		m_elapsedTime += _deltaTime;
		switch (m_clearState)
		{
		case 0:
			if (2.f <= m_elapsedTime) m_clearState = 1;
			break;

		case 1:
			m_isShowSpacebar = true;
			if (input->IsKeyState(KEY::SPACE, KEY_STATE::TAP))
			{
				m_clearState = 2;
				m_elapsedTime = 8.f;
			}
			else if (8.f <= m_elapsedTime)
				m_clearState = 2;
			break;

		case 2:
			GetCameraManager()->FadeOutCamera(1.5f, false); // 페이트 아웃
			m_clearState = 3;
			break;

		case 3:
			if (9.4f <= m_elapsedTime)
				m_clearState = 4;
			break;

		case 4:
			GetSceneManager()->RegisterNextScene(L"Ending");
			break;
		}
	}



}

void ClearCheck::DebugRender(D2DRenderer* _d2DRenderer)
{
	wstring info = L"클리어 : " + std::to_wstring(m_tagetIndex) + L" 현재 : " + std::to_wstring(m_clearIndex);

	_d2DRenderer->DrawTextW(info,  Vector2(-500.f,-500.f), Vector2(0.f, 0.f), D2D1::ColorF::Yellow);

}

void ClearCheck::Render(D2DRenderer* _d2DRenderer)
{
	if (m_sceneName == L"Stage1" && m_isShowImage)
	{
		_d2DRenderer->DrawBitmap(L"S2_01", Vector2::Zero);
	}
	if (m_sceneName == L"Stage2" && m_isShowImage)
	{
		_d2DRenderer->DrawBitmap(L"S3_01", Vector2::Zero);
	}
	if (m_sceneName == L"Stage3" && m_isShowImage)
	{
		_d2DRenderer->DrawBitmap(L"S4_01", Vector2::Zero);
	}
	if (m_isShowSpacebar)
	{
		_d2DRenderer->DrawBitmap(L"space bar", Vector2(800,-475));
	}
}
