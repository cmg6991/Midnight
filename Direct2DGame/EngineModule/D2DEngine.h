#pragma once


// 전방선언
class GameProcess;
class D2DRenderer;
/// <summary>
/// 게임에 필요한 엔진을 설계하자~! 
/// 1.먼저 엔진과 그래픽 모듈을 나누어서 설계
/// 2.엔진과 게임 프로세스도 나누는 방법을 맞는걸까?
/// 3.D2D 헤더파일을 잘사용해보자
/// 
/// 
/// 2023.06.10 이기태
/// </summary>
class D2DEngine
{
public:
	D2DEngine();
	~D2DEngine();
		
	// 엔진 명시적 초기화 함수 
	void Initalize(HINSTANCE _hInstance, int _nCmdShow);

	void Process();

	// 엔진 명시적 종료 함수
	void Finalize();
private:
	void WindowInitalize(HINSTANCE _hInstance, int _nCmdShow);

private:
	// 화면 해상도
	const int m_screenWidth = 1920;
	const int m_screenHeight = 1080;

	HINSTANCE m_hInstance;
	// 메인 윈도우 핸들
	HWND m_hWnd;
	// 랜더링을 담당
	D2DRenderer* m_d2DRenderer;

	GameProcess* m_gameProcess;
};

