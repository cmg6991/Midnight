#pragma once
#include <MonoBehaviour.h>


class LightWaver : public MonoBehaviour
{
public:
	LightWaver();
	~LightWaver();
	Component* Clone() override;

public:
	void Start() override;
	void Update(float _deltaTime) override;
	
private:
	Transform* m_transform;
	
	float m_amplitute;	//진폭
	float m_frequency;	//각속도
	float m_phaseShift;	//위상지연
	Vector2 m_origin;		//시작 위치
	float m_time;		//내부 시간
	float m_speed;		//속도
};

