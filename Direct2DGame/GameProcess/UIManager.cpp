#include "GameProcessPCH.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ManagerSet.h"
#include "InputManager.h"
#include "Component.h"
#include "GameObject.h"
#include "MouseEvent.h"

UIManager::UIManager()
	:m_sceneManager(nullptr)
	,m_focusedUI(nullptr)
	,m_managerSet(nullptr)
{}

UIManager::~UIManager()
{

}
void UIManager::Initalize(SceneManager* _sceneManager, ManagerSet* _managerSet)
{
	m_sceneManager = _sceneManager;
	m_managerSet = _managerSet;
}

void UIManager::Update()
{
	/// 현재 포커스 중인 UI 확인
	m_focusedUI = GetFocusedUI();

	// 현재 포커스 중인 UI가 없는 경우
	if (!m_focusedUI)
		return;

	const InputManager* input = m_managerSet->GetInputManager();

	/// 부모오브젝트의 자식중에 실제로  포커스된 UI
	GameObject* targetUI = GetTargetedUI(m_focusedUI);

	if (targetUI == nullptr)
		return;

	KEY_STATE LBtnState = input->GetKeyState(KEY::LMOUSE);
	MouseEvent* ui = targetUI->GetComponent<MouseEvent>();
	assert(ui);

	if (LBtnState == KEY_STATE::TAP)
	{
		targetUI->OnMouseDown();
		ui->SetLBtnDown(true);
	}
	else if (LBtnState == KEY_STATE::AWAY)
	{
		targetUI->OnMouseUp();

		if (ui->IsLBtnDown())
		{
			targetUI->OnMouseClicked();
		}

		ui->SetLBtnDown(false);
	}
}

void UIManager::Finalize()
{
	
}

void UIManager::SetFocusedUI(GameObject* _object) const
{
	if (m_focusedUI == _object || nullptr == _object)
	{
		m_focusedUI = _object;
		return;
	}

	// TODO 처리해야함 
	// 포커스된 오브젝트를 배열의 마지막으로 보내기 
	m_focusedUI = _object;
	Scene* currentScene = m_sceneManager->GetCurrentScene();
}

GameObject* UIManager::GetFocusedUI()
{
	const InputManager* input = m_managerSet->GetInputManager();
	
	// LMouse 입력이 있으면 포커스중인 UI를 갱신한다.
	if (!input->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP))
	{
		return m_focusedUI;
	}

	// 이전프레임에 포커스 중인 UI
	GameObject* focusedUI = m_focusedUI;

	// 현재 포커스중인 UI 찾기
	Scene* scene = m_sceneManager->GetCurrentScene();
	
	/// BAKC_UI는 FRONT_UI보다 항상 뒤에 레이어 그려져야 한다.
	vector<GameObject*>& backUIGroup = scene->GetUIGroupObject(OBJECT_TYPE::BACK_UI);
	
	auto targetBack = backUIGroup.end();

	for (auto iter = backUIGroup.begin(); iter != backUIGroup.end(); ++iter)
	{
		MouseEvent* ui = (*iter)->GetComponent<MouseEvent>();

		
		if (ui == nullptr)
			continue;

		if (ui->IsMouseOn())
		{
			targetBack = iter;
		}
	}

	/// FRONT_UI는 항상 앞에 그려지는 오브젝트 타입이다.
	vector<GameObject*>& frontUIGroup = scene->GetUIGroupObject(OBJECT_TYPE::FRONT_UI);

	auto targetFront = frontUIGroup.end();

	for (auto iter = frontUIGroup.begin(); iter != frontUIGroup.end(); ++iter)
	{
		MouseEvent* ui = (*iter)->GetComponent<MouseEvent>();
		// 마우스가 올라간 상태와 부모UI인 경우만
		if (ui->IsMouseOn() && (*iter)->GetParent() == nullptr)
		{
			targetFront = iter;
		}
	}

	// 이벤에 포커스된 UI가 없는 경우
	if (targetBack == backUIGroup.end() && targetFront == frontUIGroup.end())
	{
		return nullptr;
	}

	/// 그룹백테내에서 가장 후순위로 빼기 
	/// 포커스된 frontUI가 있는 경우
	if (targetFront != frontUIGroup.end())
	{
		focusedUI = (*targetFront);
		frontUIGroup.erase(targetFront);
		frontUIGroup.push_back(focusedUI);
	}
	else /// 포커스된 backUI만 있는경우
	{
		focusedUI = (*targetBack);
		backUIGroup.erase(targetBack);
		backUIGroup.push_back(focusedUI);
	}
	return focusedUI;
}

GameObject* UIManager::GetTargetedUI(GameObject* _parent)
{
	const InputManager* input = m_managerSet->GetInputManager();
	KEY_STATE LBtnState = input->GetKeyState(KEY::LMOUSE);

	// 부모 UI포함, 자식UI들중 실제 타겟팅된 UI를 가져온다
	GameObject* targetUI = nullptr;

	list<GameObject*> q;
	vector<GameObject*> noneTarget;

	q.push_back(_parent);
	

	while (!q.empty())
	{
		GameObject* object = q.front();
		q.pop_front();

		MouseEvent* ui = object->GetComponent<MouseEvent>();

		if (ui->IsMouseOn())
		{
			if (nullptr != targetUI)
			{
				noneTarget.push_back(targetUI);
			}

			targetUI = object;
		}
		else
		{
			noneTarget.push_back(object);
		}

		vector<GameObject*>& children = object->GetChildren();
		for (auto child : children)
		{
			q.push_back(child);
		}
	}

	if (LBtnState == KEY_STATE::AWAY)
	{
		for (auto object : noneTarget)
		{
			MouseEvent* ui = object->GetComponent<MouseEvent>();
			ui->SetLBtnDown(false);
		}
	}
	return targetUI;
}
