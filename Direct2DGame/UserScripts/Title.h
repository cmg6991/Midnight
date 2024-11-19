#pragma once
#include <MonoBehaviour.h>
class Title : public MonoBehaviour
{
public:
	Title();
	~Title();
	Component* Clone() { return nullptr; }

	void Start() override;
	void Update(float _deltaTime) override;

private:
	float m_timer;
	float m_time;
	UINT m_currentIndex;
	Animator* m_ani;
};

