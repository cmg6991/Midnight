#pragma once
#include <MonoBehaviour.h>
class ESC :
    public MonoBehaviour
{
public:
    ESC();
    ~ESC();
    Component* Clone() { return nullptr; }

    void Start() override;
    void Update(float _deltaTime) override;
    void OnMouseClicked() override;
    void UIFadeOut(string m_myObjectName);

private:
    string m_myObjectName;
    bool isSwitchOn;
	float fadeAlpha;
	float m_deltaTime;
};

