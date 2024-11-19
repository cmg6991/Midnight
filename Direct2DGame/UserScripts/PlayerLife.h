#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 
/// 23.08.21 손서희
/// </summary>


/// 플레이어의 체력을 관리 & 표시하는 UI
class PlayerLife : public MonoBehaviour
{
public:
	PlayerLife();
	~PlayerLife();
	Component* Clone() override { return nullptr; }

public:
	void Start() override;
	void Update(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer);

	UINT GetLife() { return m_remainLife; }
	void DicreaseLife();



private:
	UINT m_remainLife;
	const vector<wstring> m_texture = {L"쿠키0", L"쿠키1", L"쿠키2", L"쿠키3"};
	ParticleSystem* m_particle;
};

