#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 스테이지 클리어를 체크해주는 컴포넌트 
/// </summary>
class ClearCheck :
    public MonoBehaviour
{
public:
    ClearCheck();
    ~ClearCheck();
    Component* Clone() override;
    void Start() override;

    wstring GetCutName() const { return m_cutName; }
    void SetCutName(wstring val) { m_cutName = val; }
public:
    void Update(float _deltaTime) override;
    void DebugRender(D2DRenderer* _d2DRenderer) override;
    void Render(D2DRenderer* _d2DRenderer) override;

	int GetClearIndex() const { return m_clearIndex; }
    void AddClearIndex() { m_clearIndex++; }
    int GetTagetIndex() const { return m_tagetIndex; }
    void SetTagetIndex(int val) { m_tagetIndex = val; }

    bool IsClearStage() { return m_isFinished; }

private:
    int m_clearIndex; // 현재 클리어한 목표
    int m_tagetIndex; // 클리어 해야하는 목표 갯수 
    bool m_isFinished;
    float m_elapsedTime;
    bool m_isClearStage; // 
    bool m_isShowImage;
    bool m_isShowSpacebar;

    wstring m_cutName;


    wstring m_sceneName;

    UINT m_clearState;
};

