#pragma once
#include "MonoBehaviour.h"

class RabbitTunnelBubble : public MonoBehaviour
{
public:
	RabbitTunnelBubble();
	~RabbitTunnelBubble();

	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;
	/// 가장 기본적인 랜더링 이벤트
	void Render(D2DRenderer* _d2DRenderer) override;
	void SetRabbitTunnel(GameObject* val) { m_rabbitTunnel = val; }

private:
	GameObject* m_rabbitTunnel;
	TextureRenderer* m_textureRenderer;
	Transform* m_transform;
	Vector2 m_position;
	float 	m_renderTime;
};

