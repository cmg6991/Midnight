#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// 씬변경 버튼 용도 컴포넌트
/// 
/// 2023.8.6 1:31 gitae
/// </summary>
class SceneChangeButton :
    public MonoBehaviour
{
public:
    SceneChangeButton();
    ~SceneChangeButton();

    Component* Clone() override;

    void SetSceneName(const wstring& _name) { m_chageScneName = _name; }
    
    void OnMouseClicked() override;
    
private:
    wstring m_chageScneName; // 버튼 눌렀을때 변경하는 씬 이름 
   
};

