#pragma once
#include <MonoBehaviour.h>
class Candle : public MonoBehaviour
{
public:
	Candle();
	~Candle();
	Component* Clone() { return  nullptr; }
	void Start() override;

	void SetClearCheck(GameObject* val) { m_clearCheck = val; }
public:
	void Update(float _deltaTime);
	void OnTriggerStay(const Collision& _collision);
	void DebugRender(D2DRenderer* _d2DRenderer);
	void LightCandle();
	bool IsLightOn() { return m_isLightOn; }

private:
	GameObject* m_clearCheck;

	PointLightRenderer* m_pointLight;
	CircleCollider* m_lightCollider;
	const InputManager* m_inputManager;

	bool m_isLightOn;
	bool m_isWorkingDone;

	//±ôºýÀÓ °ü·Ã
	float m_timer;
	float m_changeTime;
	int m_isGoingLighter;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<float> dis;

	//ÀÚ½Ä ºÒºû
	TextureRenderer* m_lightTexture;
};

