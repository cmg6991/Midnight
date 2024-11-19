#pragma once

#include "MonoBehaviour.h"

class Transform;

/// <summary>
/// 연출 시스템 컴포넌트  
/// Diretor 클래스가 Actor들에게 명령을 내린다.
/// 
/// 2023.8.9 15:10 gitae
/// </summary>
class Actor :
    public MonoBehaviour
{
public:
    Actor();
    ~Actor();
    Component* Clone() override;

    Vector2 GetOffset() const { return m_offset; }
    void SetOffset(Vector2 _offset) { m_offset = _offset; }
    Vector2 GetTextOffset() const { return m_textOffset; }
    void SetTextOffset(Vector2 val) { m_textOffset = val; }
    Vector2 GetInverseOffset() const { return m_inverseOffset; }
    void SetInverseOffset(Vector2 val) { m_inverseOffset = val; }
private:
    void Start() override;
    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;

public:
    void SetInverse(bool _isFilp) { m_isInverse = _isFilp; }
    // 말풍선 대사 연출을 지시한다. 
    void DirectTalking(const TalkingInfomation& _info, int _actingOrder);

private: 
    Transform* m_transform;
    int m_actingOrder; // 현재 연출 순서 
    size_t m_currentIndex; // 현재 출력중인 문자갯수
    bool m_isActing; // 현재 연출중인지 
    wstring m_outputText; // 현재 출력중인 텍스트 

    Vector2 m_scale = Vector2(360.f, 120.f);
    Vector2 m_offset; // 말풍선 오프셋
    Vector2 m_textOffset; 
    Vector2 m_inverseOffset;

    bool m_isInverse; // 말풍선 위치 반전 여부 
    float m_elapsedTime;

    const float END_TEXT_TIME = 1.8f;

    TalkingInfomation m_talkingInfomation;

};

