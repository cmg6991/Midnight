#pragma once
#include <MonoBehaviour.h>

class PopupBtnUI :
    public MonoBehaviour
{
public:
    PopupBtnUI();
    ~PopupBtnUI();
    Component* Clone() override;

    void Start() override;
    void OnMouse() override;
    void Update(float _deltaTime) override;
    void OnMouseClicked() override;

    wstring GetAniName() const { return m_aniName; }
    void SetAniName(wstring val) { m_aniName = val; }
private:
    wstring m_aniName;
    Animator* m_animator;
    TextureRenderer* m_textureRenderer;


    bool m_onMouse;
};

