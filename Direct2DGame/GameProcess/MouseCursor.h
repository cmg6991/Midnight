#pragma once
#include "MonoBehaviour.h"

class MouseCursor : public MonoBehaviour
{
public:
	MouseCursor();
	~MouseCursor();

	void Start() override;
	void Update(float _dt) override;
	void Render(D2DRenderer* _d2DRenderer) override;
	Component* Clone() override;
	void SetActive(bool _arg) { m_isActive = _arg; }


private:
	const InputManager* m_inputManager;
	bool m_isActive;
};

