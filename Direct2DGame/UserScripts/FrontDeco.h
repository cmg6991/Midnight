#pragma once
#include <Component.h>


/// <summary>
/// 플레이어가 가려지면 반투명해지는 장식용 오브젝트
/// </summary>
class FrontDeco : public Component
{
public:
	FrontDeco();
	~FrontDeco();
	Component* Clone() override;

public:
	void Update(float _deltaTime);
	void OnTriggerEnter(const Collision& _collision) override;
	void OnTriggerExit(const Collision& _collision) override;

private:
	TextureRenderer* m_textureRenderer;
	int m_state; // 0 : 변경X,  1 : 알파 증가, -1 : 알파 감소
	const float m_alphaHold = 0.65f;
};

