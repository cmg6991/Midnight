#pragma once
#include <Component.h>

class Chaser;
class SoundMaker : public Component
{
public:
	SoundMaker();
	~SoundMaker();
	Component* Clone() { return nullptr; }

public:
	void Start() override;
	void Update(float _deltaTime) override;

	void OnTriggerEnter(const Collision& _collision);
	void SetChaser(Chaser* _chaserComp) { m_chaser = _chaserComp; }
	void DebugRender(D2DRenderer* _d2DRenderer) override;

private:
	Chaser* m_chaser;
	Vector2 m_thisPosition;
	bool m_isPlaySound;

};

