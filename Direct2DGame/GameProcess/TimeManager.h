#pragma once

// deltaTime을 계산해주는 클래스
class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Initalize(const Vector2& _screenSize);

	// deltaTime을 반환해준다
	double Update();
	void DebugRender(D2DRenderer* _d2dRenderer);
	void Finalize();

	float GetDeltaTime() const{ return static_cast<float>(m_deltaTime); }

private:
	LARGE_INTEGER m_curentCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_frequency;

	Vector2 m_screenSize;

	double m_deltaTime;
	double m_elapsedTime;
	int m_updateCount;
	int m_fps;
};

