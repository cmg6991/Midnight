#pragma once
#include "MonoBehaviour.h"

class UIComponent : public MonoBehaviour
{
public:
	UIComponent();
	~UIComponent();
	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;
	/// 가장 기본적인 랜더링 이벤트
	void Render(D2DRenderer* _d2DRenderer) override;

	void PostRender(D2DRenderer* _d2DRenderer) override;
	/// 디버그 전용 랜더링 함수 F5를 온오프
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnMouse() override;
	void OnMouseClicked() override;

	void UIFadeOut(string m_myObjectName);


private:
	string m_myObjectName; // 마우스 관련 이벤트를 실행할 버튼을 찾는 이름

	// 가져온 컴포넌트
	MouseEvent* m_mouseEvent;
	TextureRenderer* m_textureRenderer;
	Transform* m_transform;
	Animator* m_animator;
	// 매니저
	const SceneManager* m_mySceneManager;
	const InputManager* m_myInputManager;
	const CameraManager* m_myCameraManager;
	Scene* m_scene;
	// fadeout
	bool isSwitchOn;
	float fadeAlpha;
	float m_deltaTime;

	const wchar_t* gameStartOnMouse = L"gameStartOnMouse";
	const wchar_t* crewOnMouse = L"crewOnmouse";
	const wchar_t* gameExitOnMouse = L"gameExitOnMouse";
};

