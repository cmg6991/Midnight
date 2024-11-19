#pragma once
#include "MonoBehaviour.h"

class PopupWindow;

/// <summary>
///  팝업창에서 재시작 버튼을 위한 컴포넌트
/// </summary>
class PlayButton :
    public MonoBehaviour
{
public:
    PlayButton();
    ~PlayButton();
    Component* Clone() override;

    void Start() override;

public:
    void OnMouseClicked() override;
    PopupWindow* m_popupWindow;
};

