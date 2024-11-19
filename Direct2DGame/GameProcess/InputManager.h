#pragma once

struct KeyInfo
{
	KEY_STATE state; // 키의 상태값
	bool      prevPush;  // 이전 프레임에서 눌렸는지 여부
};

class CameraManager; 

/// <summary>
/// 입력을 담당해준다.
/// 키보드, 마우스등의 입력데이터를 프레임마다 갱신하여
/// 관리하고 출력한다.
/// 
/// </summary>
class InputManager
{
public:
	InputManager();
	~InputManager();

	void Initalize(HWND _main, CameraManager* _cameraManager);
	void Update();
	void Finalize();

	Vector2 GetWorldMousePosition() const { return m_worldMousePosition; }
	Vector2 GetScreendMousePosition() const { return m_screenMousePosition; }
	Vector2 GetCameraMousePosition() const { return m_cameraMousePosition; }

	KEY_STATE GetKeyState(KEY _key)const { return m_keyInfo[static_cast<int>(_key)].state; }
	bool IsKeyState(const KEY& _key, const KEY_STATE& _state) const;
private:
	CameraManager* m_cameraManager;

	// 메인 윈도우 핸들
	HWND m_hwnd;

	// 이번 프레임 마우스 위치
	Vector2 m_worldMousePosition;
	Vector2 m_cameraMousePosition;
	Vector2 m_screenMousePosition;

	// 키 정보들을 담은 배열
	vector<KeyInfo> m_keyInfo;

	// KEY 값을 가상키값과 매칭시켜주는 배열
	const int m_matchVK[static_cast<int>(KEY::LAST)];
};

