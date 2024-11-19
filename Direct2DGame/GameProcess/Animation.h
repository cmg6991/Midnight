#pragma once

class Animator;

struct Frame
{
	Vector2 leftTop; // 좌상단 좌표
	Vector2 slice; 
	Vector2 offset;
	FLIP_TYPE flipType;
	float duration;
};


/// <summary>
/// 애니메이션 정보를 저장하는 클래스이다
/// 
/// Animation은 오직 Animator에 종속적인 관계로 설정하자
/// 
/// </summary>
class Animation
{
public:
	Animation();
	~Animation();
	
	Animation(const Animation& _other);

public:
	bool IsFinish() { return m_finish; }
	void SetFrame(int _index)
	{
		m_finish = false;
		m_currentFrame = _index;
		m_elapsedTime = 0.f;
	}

	Frame& GetFrame(int _index) { return m_frames[_index]; }
	size_t GetMaxFrame() { return m_frames.size(); }

public: 
	void Update(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer, bool _onEffect, float _ratio, float _alpha);
	void SetAnimator(Animator* _animator) { m_animator = _animator; }
	void SetFlipType(FLIP_TYPE _type);

	// 애니메이션 정보 생성
	void Create(const wstring& _name, const wstring& _textureKey, Vector2 _leftTop
		, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount, FLIP_TYPE _type);

	// 애니메이션 정보 생성
	void Create2(const wstring& _name, const wstring& _textureKey, Vector2 _leftTop
		, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount, FLIP_TYPE _type
	, Vector2 _nextLineOffSet, int _width);


public:
	const wstring& GetName() {return m_name;}

private:
	wstring m_name; // 애니메이션 이름
	wstring m_textureKey; // 텍스처 키값
	Animator* m_animator; // 애니메이션을 소유하고 있는 애니메이터
	vector<Frame> m_frames; // 모든 프레임 정보
	int m_currentFrame; // 현재 프레임 인덱스
	float m_elapsedTime; 
	bool m_finish; // 재생이 끝난지
};

