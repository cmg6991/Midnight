#pragma once
#include "Component.h"

class Animation;

/// <summary>
/// 애니메이션 출력을 담당하는 컴포넌트이다
/// 애니메이터는 여러가지의 애니메이션을 가질수 있는 구조이다
///
/// 
/// 미리 생성한 애니메이션 파일을 읽는 필요해보임 -> 재활용가능성 증가
/// 
/// 20203.07.04 오후 10시 
/// </summary>
class Animator :
    public Component
{
public:
    Animator();
    ~Animator();

    Component* Clone() override;



    float GetTimeRatio() const { return m_timeRatio; }
    void SetTimeRatio(float val) { m_timeRatio = val; }
    bool IsShow() const { return m_isShow; }
    void SetShow(bool val) { m_isShow = val; }
    float GetAlpha() const { return m_alpha; }
    void SetAlpha(float val) { m_alpha = val; }
public:

    /// <summary>
    /// 애니메이터가 가지는 애니메이션을 생성
    /// </summary>
    /// <param name="_name">애니메이션 이름</param>
    /// <param name="_textureKey">텍스처 키값</param>
    /// <param name="_startLeftTop">텍스처의 시작 좌상단</param>
    /// <param name="_sliceSize">스프라이트 한개의 크기</param>
    /// <param name="_sliceOffeset">스프라이트 간격</param>
    /// <param name="_duration">애니메이션 한 프레임의 시간</param>
    /// <param name="_frameCount">스프라이트 갯수</param>
    void CreateAnimation(const wstring& _name, const wstring& _textureKey
    , Vector2 _startLeftTop, Vector2 _sliceSize, Vector2 _sliceOffset
    , float _duration, UINT _frameCount, FLIP_TYPE _type);

	void CreateAnimation2(const wstring& _name, const wstring& _textureKey
		, Vector2 _startLeftTop, Vector2 _sliceSize, Vector2 _sliceOffset
		, float _duration, UINT _frameCount, FLIP_TYPE _type 
        , Vector2 _nextLineOffset, int _width);


    // 애니메이션 찾기
    Animation* FindAnimation(const wstring& _name);

    // 애니메이션 재생
    void Play(const wstring& _name, bool _repeat);

    void LateUpdate(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;
    void Reset();
    void Reset(const wstring& _name);
    void SetFlipType(const wstring& _animation, FLIP_TYPE _type);


    // 현재 재생중인 애니메이션 반환
    const wstring& GetCurrentAnmationName();
    

	Animation* GetCurrentAnmation() {
        return m_currentAnimation;
	}

	bool IsEffectOn() const { return m_onEffect; }
	void SetEffect(bool val) { m_onEffect = val; }
	float GetEffectRatio() const { return m_effectRatio; }
	void SetEffectRatio(float val) { m_effectRatio = val; }

    Vector2 GetOffset() { return m_offset; }
    void SetOffset(Vector2 _offset) { m_offset = _offset; }

private:
    map<wstring, Animation*> m_animations; // 모든 animation 정보
    Animation* m_currentAnimation; // 현재 재생중인 애니메이션
    bool m_repeat; // 반복재생여부
    bool m_onEffect; // 얼기효과
    float m_effectRatio; // 얼리기 효과 비율 0.f~1.f
    float m_timeRatio;
    bool m_isShow;

    Vector2 m_offset;

    float m_alpha;
};

