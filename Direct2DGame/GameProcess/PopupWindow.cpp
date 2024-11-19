#include "GameProcessPCH.h"
#include "PopupWindow.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MouseCursor.h"

PopupWindow::PopupWindow()
	:Component(CALL_ORDER::UI,typeid(this).name())
	,m_isActive(false), m_cursor(nullptr)
{

}

PopupWindow::~PopupWindow()
{

}

Component* PopupWindow::Clone()
{
	// 팝업창은 복사하지 않는다.
	assert(!L" 팝업창은 복사하지 않습니다.");

	return nullptr;
}

void PopupWindow::Render(D2DRenderer* _d2DRenderer)
{
	if (IsActive())
	{
		_d2DRenderer->DrawBitmap(L"SpotLightBase", Vector2::Zero, 0.f, 0.5f);
		_d2DRenderer->DrawBitmap(L"Popup", Vector2(-570.f,400.f));
	}
}

void PopupWindow::Start()
{
	// 자식 오브젝트들을 비활성화
	auto& children = GetComponent<Transform>()->GetChildren();

	for (auto& child : children)
	{
		child->SetActive(false);
	}

	//마우스 커서 오브젝트를 가져온다.
	const vector<GameObject*>& objs = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::MOUSE);
	m_cursor = objs[0]->GetComponent<MouseCursor>();
}

void PopupWindow::Update(float _deltaTime)
{
	const InputManager* input = GetInputManager();
		
	
	if (input->IsKeyState(KEY::ESC, KEY_STATE::TAP))
	{
		m_isActive = !m_isActive;
	}

	const SceneManager* scneneManager = GetSceneManager();
	auto& children = GetComponent<Transform>()->GetChildren();

	if (IsActive())
	{
		//마우스 커서를 보인다
		m_cursor->SetActive(true);
		
		scneneManager->SetPause(true);

		for (auto& child : children)
		{
			child->SetActive(true);
		}
	}
	else
	{
		//마우스 커서를 숨긴다
		scneneManager->SetPause(false);
		m_cursor->SetActive(false);

		for (auto& child : children)
		{
			child->SetActive(false);
		}
	}
}

void PopupWindow::SetActive(bool _isActive)
{
	m_isActive = _isActive;

	const SceneManager* scneneManager = GetSceneManager();
	auto& children = GetComponent<Transform>()->GetChildren();

	if (m_isActive)
	{
		scneneManager->SetPause(true);

		for (auto& child : children)
		{
			child->SetActive(true);
		}
	}
	else
	{
		scneneManager->SetPause(false);

		for (auto& child : children)
		{
			child->SetActive(false);
		}
	}
}
