#pragma once
class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Initalize();

	double Update();

private:
	LARGE_INTEGER m_currentCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_frequency;

	double m_deltaTime;
};

