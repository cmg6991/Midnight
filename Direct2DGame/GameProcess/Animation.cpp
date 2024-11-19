#include "GameProcessPCH.h"
#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"
#include "Transform.h"

Animation::Animation()
	:m_animator(nullptr)
	,m_textureKey{}
	,m_elapsedTime(0.f)
	,m_currentFrame(0)
	,m_finish(false)
{

}

Animation::Animation(const Animation& _other)
	:m_animator(nullptr)
	,m_textureKey(_other.m_textureKey)
	,m_elapsedTime(_other.m_elapsedTime)
	,m_currentFrame(_other.m_currentFrame)
	,m_finish(_other.m_finish)
	,m_frames(_other.m_frames)
	,m_name(_other.m_name)
{
	
}

Animation::~Animation()
{

}

void Animation::Update(float _deltaTime)
{
	if (m_finish)
		return;
	m_elapsedTime += _deltaTime;

	/// 다음프레임으로 넘어가야함
	if (m_frames[m_currentFrame].duration < m_elapsedTime)
	{
		m_elapsedTime -= m_frames[m_currentFrame].duration;
		++m_currentFrame;

		// 마지막 프레임인 경우
		if (m_frames.size() <= m_currentFrame)
		{
			m_currentFrame = -1; // 종료된 프레임이라는 뜻
			m_finish = true;
		}

		m_elapsedTime = 0.f;
	}

}


void Animation::Render(D2DRenderer* _d2DRenderer, bool _onEffect, float _ratio, float _alpha)
{
	if (m_finish)
		return;

	Transform* transform = m_animator->GetComponent<Transform>();
	Vector2 position = transform->GetPosition() + m_animator->GetOffset();
	float rotation = transform->GetRotation();

	position += m_frames[m_currentFrame].offset; // offset만큼 추가 이동
	Vector2 leftTop = m_frames[m_currentFrame].leftTop;
	Vector2 sliceSize = m_frames[m_currentFrame].slice;

	// 효과를 적용해서 랜더린 한다.
	if (false)//_onEffect)
	{
		_d2DRenderer->DrawFreezeBitmap(m_textureKey, position, leftTop, sliceSize, _ratio, rotation, _alpha, m_frames[m_currentFrame].flipType);
	}
	else
	{
		_d2DRenderer->DrawBitmap(m_textureKey, position, leftTop, sliceSize, rotation, _alpha, m_frames[m_currentFrame].flipType);
	}
}

void Animation::SetFlipType(FLIP_TYPE _type)
{
	for (auto& frame : m_frames)
	{
		frame.flipType = _type;
	}
}

void Animation::Create(const wstring& _name, const wstring& _textureKey, Vector2 _leftTop, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount, FLIP_TYPE _type)
{
	m_name = _name;
	m_textureKey = _textureKey;

	for (UINT i = 0; i < _frameCount; ++i)
	{
		Frame frame{};
		frame.duration = _duration;
		frame.slice = _sliceSize;
		frame.leftTop = _leftTop + _step * static_cast<float>(i);
		frame.flipType = _type;
		m_frames.push_back(std::move(frame));
	}
}

void Animation::Create2(const wstring& _name, const wstring& _textureKey, Vector2 _leftTop, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount, FLIP_TYPE _type, Vector2 _nextLineOffSet, int _width)
{
	m_name = _name;
	m_textureKey = _textureKey;

	for (UINT i = 0; i < _frameCount; ++i)
	{
		Frame frame{};
		frame.duration = _duration;
		frame.slice = _sliceSize;

		int line = i / _width;

		frame.leftTop = _leftTop + _step * static_cast<float>(i%_width) + _nextLineOffSet * static_cast<float>(i/_width);
		frame.flipType = _type;
		m_frames.push_back(std::move(frame));
	}

}
