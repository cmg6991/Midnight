#pragma once
#include <MonoBehaviour.h>
class Candle;
class Achievement2 : public MonoBehaviour
{
public:
	Achievement2();
	~Achievement2();
	Component* Clone() { return nullptr; }

public:
	void Start() override;
	void Update(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer) override;



private:
	vector<Candle*> m_candles;
	vector<bool> m_isOn;
	Transform* m_transform;
	const InputManager* m_input;
	float m_showDuration;
	float m_showTimer;
	bool m_isOpen;

	int m_lastCount = 0;
	int m_Count = 0;
};

