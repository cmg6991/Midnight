#include "GameProcessPCH.h"
#include "BarUI.h"
#include "GameObject.h"
#include "Transform.h"

BarUI::BarUI()
	:MonoBehaviour(typeid(this).name())
	,m_barLength(0.f)
	,m_innerBarOffset(Vector2::Zero)
	,m_positionOffset(Vector2::Zero)
	,m_scale(Vector2::Zero)
	,m_innerEmptyColor(ColorF::White)
	,m_edgeColor(ColorF::Black)
	,m_innerFillBarColor(ColorF::White)
{

}

BarUI::~BarUI()
{

}

Component* BarUI::Clone()
{
	BarUI* clone = new BarUI();
	clone->m_barLength = m_barLength;
	clone->m_edgeColor = m_edgeColor;
	clone->m_innerBarOffset = m_innerBarOffset;
	clone->m_innerEmptyColor = m_innerEmptyColor;
	clone->m_positionOffset = m_positionOffset;
	clone->m_scale = m_scale;
	clone->m_innerFillBarColor = m_innerEmptyColor;

	return clone;
}

void BarUI::PostRender(D2DRenderer* _d2DRenderer)
{
	// 게임오브젝트의 위치를 가져온다
	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();

	// 오프셋 조정
	Vector2 finalPosition = position + m_positionOffset;
	Vector2 innerScale = m_scale + m_innerBarOffset;
	
	// 바깥쪽 바그리기
	_d2DRenderer->DrawFillRectangle(finalPosition, m_scale, m_edgeColor);

	// 내부 빈공간 바그리기
	_d2DRenderer->DrawFillRectangle(finalPosition, innerScale, m_innerEmptyColor);

	// 내부에 채워지는 바 그리기

	Vector2 leftTop{};
	leftTop.x = finalPosition.x - innerScale.x * 0.5f;
	leftTop.y = finalPosition.y + innerScale.y * 0.5f;
	Vector2 rightBottom{};
	rightBottom.x = leftTop.x + innerScale.x * m_barLength;
	rightBottom.y = finalPosition.y - innerScale.y * 0.5f;

	_d2DRenderer->DrawFillRectangle2(leftTop, rightBottom, m_innerFillBarColor);
}

void BarUI::SetBar(const BarUIInfo& _info)
{
	m_scale = _info.barScale;
	m_barLength = _info.barLength;
	m_edgeColor = _info.edgeColor;
	m_innerEmptyColor = _info.innerEmptyBarColor;
	m_innerFillBarColor = _info.innerFillBarColor;

	m_positionOffset = _info.positionOffset;
	m_innerBarOffset = _info.innerBarOffset;
}

void BarUI::SetBarLength(float _ratio)
{
	float ratio = FMath::Clamp(_ratio, 0.f, 1.f);
	
	m_barLength = ratio;
}
