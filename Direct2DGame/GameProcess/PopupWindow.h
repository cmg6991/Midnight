#pragma once
#include "Component.h"
class MouseCursor;

/// <summary>
///  팝업창 UI  컴포넌트
/// 
/// </summary>
class PopupWindow : public Component
{
public:
	PopupWindow();
	~PopupWindow();
	Component* Clone() override;

	void Render(D2DRenderer* _d2DRenderer) override;
	void Start() override;
	void Update(float _deltaTime) override;

	bool IsActive() const { return m_isActive; }
	void SetActive(bool _isActive);
private:
	bool m_isActive;
	MouseCursor* m_cursor;
};
 //오브젝트 타입 마우스
