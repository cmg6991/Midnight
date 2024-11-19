#pragma once

class InputManager;

class CameraManager
{
public:
	CameraManager(InputManager* inputManager);
	~CameraManager();

	
	void Update(double deltatime);

	ImVec2 GetPosition() const { return m_position; }
	void SetPosition(ImVec2 val) { m_position = val; }
	ImVec2 GetScale() const { return m_scale; }
	void SetScale(ImVec2 val) { m_scale = val; }
private:
	ImVec2 m_position;
	ImVec2 m_scale;
	
	InputManager* m_inputManager;
	float m_moveSpeed;

};

