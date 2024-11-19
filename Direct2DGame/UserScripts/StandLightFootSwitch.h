#pragma once
#include "MonoBehaviour.h"

class StandLightFootSwitch : public MonoBehaviour
{
public:
	StandLightFootSwitch();
	~StandLightFootSwitch();
	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;

	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;
	void OnCollisionStay(const Collision& _collision) override;

	bool GetFootSwitchOn() const { return m_isFootSwitchOn; }
	void SetFootSwitchOn(bool val) { m_isFootSwitchOn = val; }
private:
	bool m_isFootSwitchOn;
	GameObject* m_lightObject;
	GameObject* m_chandlierSwich;

};

