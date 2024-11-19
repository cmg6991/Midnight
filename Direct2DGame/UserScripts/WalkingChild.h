#pragma once
#include <MonoBehaviour.h>
class WalkingChild : public MonoBehaviour
{
public:
	WalkingChild();
	~WalkingChild();
	Component* Clone() { return nullptr; }

public:
	void Start() override;
	void Update(float _deltaTime) override;

private:
	Transform* m_transform;
};

