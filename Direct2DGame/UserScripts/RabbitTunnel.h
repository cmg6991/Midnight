#pragma once
#include "MonoBehaviour.h"

class RabbitTunnel : public MonoBehaviour
{
public:
	RabbitTunnel();
	~RabbitTunnel();
	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;
	/// 가장 기본적인 랜더링 이벤트
	void Render(D2DRenderer* _d2DRenderer) override;

	void PostRender(D2DRenderer* _d2DRenderer) override;
	/// 디버그 전용 랜더링 함수 F5를 온오프
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnCollisionStay(const Collision& _collision) override;

	void SetRabbit(GameObject* _rabbit) { m_rabbit = _rabbit; }

 	Vector2 GetPosition() const { return m_position; }
	bool GetisPlayer() const { return m_isPlayer; }
/*	void Player(bool val) { m_isPlayer = val; }*/
	// 	void SetPosition(Vector2 val) { m_position = val; }
private:
	GameObject* m_rabbit;
	RabbitTunnel* m_rabbitTunnel;
	Transform* m_transform;
	TextureRenderer* m_textureRenderer;

	Vector2 m_position;
	Vector2 m_tunnelPosition;
	Vector2 m_cameraPosition;
	string m_objectName;
	bool m_isPlayer;
	float m_renderTime;
	const InputManager* m_inputManager;
	const CameraManager* m_cameraManager;

	bool m_isOn;

};

