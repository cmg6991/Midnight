#pragma once


class GameObject;
class SceneManager;
class ManagerSet;

/// <summary>
///  UI들의 마우스 입력 이벤트를 관리하는 매니져
/// UI들의 뎁스를 만들어줌
/// </summary>
class UIManager 
{
public:
	UIManager();
	~UIManager();

	void Initalize(SceneManager* _sceneManager, ManagerSet* _managerSet);
	void Update();
	void Finalize();

	void SetFocusedUI(GameObject* _object) const;
private:
	GameObject* GetFocusedUI();
	GameObject* GetTargetedUI(GameObject* _parent);

private:
	mutable GameObject* m_focusedUI; // 현재 포커스 중인 오브젝트
	SceneManager* m_sceneManager;
	ManagerSet* m_managerSet;
};

