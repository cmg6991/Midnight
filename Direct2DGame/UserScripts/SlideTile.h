#pragma once
#include <MonoBehaviour.h>



class SlideTile : public MonoBehaviour
{
public:
	SlideTile();
	~SlideTile();
	Component* Clone() { return nullptr; }
	void Start() override;

	
public:
	void Update(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;
	void OnTriggerEnter(const Collision& _collision) override;

	bool GetIsMelt() { return m_isMelt; }

private:
	bool IsAffected(Vector2 candlePos, const vector<Vector2>& vertices, float distance);

private:
	TextureRenderer* m_texture;

	int m_targetCount;
	int m_currentCount;
	bool m_isMelt;
	bool m_isWorkingDone; 
};

