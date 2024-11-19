#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// ¼§µé¸®¿¡ ÄÄÆ÷³ÍÆ® 
/// </summary>
class Chandlier :
    public MonoBehaviour
{
public:
    Chandlier();
    ~Chandlier();
    Component* Clone() override;

    void SetClearCheck(GameObject* val) { m_clearCheck = val; }
public:
    void DebugRender(D2DRenderer* _d2DRenderer) override;

    // ¼§µé¸®¿¡ ÄÑ±â
    void LightOff();
    void LightOn();
    
	bool GetLightOn() const { return m_isLightOn; }
	void SetLightOn(bool val) { m_isLightOn = val; }

private:
    bool m_isLightOn;
    GameObject* m_clearCheck;
    InputManager* m_input;

    float m_showDuration;
    bool isOpen;
};

