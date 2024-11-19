#pragma once
#include "MonoBehaviour.h"


class StandLight : public MonoBehaviour
{
public:
	StandLight();
	~StandLight();

	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;
	void SetFootSwitch(GameObject* val) { m_footSwitch = val; }
private:
	bool m_isSwitchOn;
	GameObject* m_lightObject;
	GameObject* m_chandlierSwich;
	GameObject* m_footSwitch;

};

