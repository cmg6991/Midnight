#pragma once

enum class KEY_STATE
{
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
	NONE, // 눌리지 않았고, 이전에도 눌리지 않은 상태
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,

	Q, W, E, R, T, Y, U, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC, TAB,

	LMOUSE, RMOUSE,
	F1, F2, F3, F4, F5,

	LAST, //enum의 끝
};


struct KeyInfo
{
	KEY_STATE state; // 키의 상태값
	bool      prevPush;  // 이전 프레임에서 눌렸는지 여부
};

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

	void Initalize(HWND _main);
	void Update();
	void Finalize();

	KEY_STATE GetKeyState(KEY _key)const { return m_keyInfo[static_cast<int>(_key)].state; }
	bool IsKeyState(const KEY& _key, const KEY_STATE& _state) const;
	ImVec2 GetMousePosition() const { return m_mousePosition; }
private:

	// 메인 윈도우 핸들
	HWND m_hwnd;

	// 키 정보들을 담은 배열
	vector<KeyInfo> m_keyInfo;

	// KEY 값을 가상키값과 매칭시켜주는 배열
	const int m_matchVK[static_cast<int>(KEY::LAST)];

	ImVec2 m_mousePosition;
};

