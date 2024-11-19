#include "GameProcessPCH.h"
#include "Animator.h"
#include "Animation.h"

Animator::Animator()
	:Component(CALL_ORDER::ANIMATOR, typeid(this).name())
	, m_animations{}
	, m_currentAnimation(nullptr)
	, m_repeat(false)
	, m_onEffect(false)
	, m_effectRatio(0.f)
	, m_timeRatio(1.f)
	,m_offset()
	, m_alpha(1.f)
	, m_isShow(true)
{}

Animator::~Animator()
{
	//  모든 애니메이션 삭제
	for (auto& iter : m_animations)
	{
		if (iter.second != nullptr)
		{
			delete iter.second;
		}
	}
}

Component* Animator::Clone()
{
	Animator* clone = new Animator();

	clone->m_animations = m_animations;
	for (auto& iter : m_animations)
	{
		iter.second->SetAnimator(clone);
	}

	clone->m_currentAnimation = m_currentAnimation;
	clone->m_repeat = m_repeat;

	return clone;
}


void Animator::CreateAnimation(const wstring& _name, const wstring& _textureKey, Vector2 _startLeftTop, Vector2 _sliceSize, Vector2 _sliceOffset, float _duration, UINT _frameCount, FLIP_TYPE _type)
{
	Animation* animation = FindAnimation(_name);
	assert(nullptr == animation);

	// 애니메이션 생성
	animation = new Animation();
	animation->SetAnimator(this);
	animation->Create(_name, _textureKey, _startLeftTop
		, _sliceSize, _sliceOffset, _duration, _frameCount, _type);

	// 애니메이션 저장
	m_animations.insert(make_pair(_name, animation));
}

void Animator::CreateAnimation2(const wstring& _name, const wstring& _textureKey, Vector2 _startLeftTop, Vector2 _sliceSize, Vector2 _sliceOffset, float _duration, UINT _frameCount, FLIP_TYPE _type, Vector2 _nextLineOffset, int _width)
{
	Animation* animation = FindAnimation(_name);
	assert(nullptr == animation);

	// 애니메이션 생성
	animation = new Animation();
	animation->SetAnimator(this);
	animation->Create2(_name, _textureKey, _startLeftTop
		, _sliceSize, _sliceOffset, _duration, _frameCount, _type, _nextLineOffset, _width);

	// 애니메이션 저장
	m_animations.insert(make_pair(_name, animation));
}

Animation* Animator::FindAnimation(const wstring& _name)
{
	auto iter = m_animations.find(_name);

	if (iter != m_animations.end())
	{ 
		return iter->second;
	}

	return nullptr;
}

void Animator::Play(const wstring& _name, bool _repeat)
{
	m_currentAnimation = FindAnimation(_name);

	m_repeat = _repeat;
}

void Animator::LateUpdate(float _deltaTime)
{
	if (nullptr != m_currentAnimation)
	{
		m_currentAnimation->Update(_deltaTime* GetTimeRatio());

		// 반복재생인 경우 다시 재생
		if (m_repeat && m_currentAnimation->IsFinish())
		{
			m_currentAnimation->SetFrame(0);
		}
	}
}

void Animator::Render(D2DRenderer* _d2DRenderer)
{
	if (nullptr != m_currentAnimation && m_isShow)
	{
		m_currentAnimation->Render(_d2DRenderer, IsEffectOn(), m_effectRatio,m_alpha);
	}


}

void Animator::Reset()
{
	for (auto& animation : m_animations)
	{
		animation.second->SetFrame(0);
	}
}

void Animator::Reset(const wstring& _name)
{
	auto iter = m_animations.find(_name);

	assert(iter != m_animations.end());

	iter->second->SetFrame(0);
}

void Animator::SetFlipType(const wstring& _animation, FLIP_TYPE _type)
{
	auto iter = m_animations.find(_animation);
	
	iter->second->SetFlipType(_type);
}

const wstring& Animator::GetCurrentAnmationName()
{
	return m_currentAnimation->GetName(); 
}

