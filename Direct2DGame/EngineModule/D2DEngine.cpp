
#include "EnginePCH.h"
#include "D2DEngine.h"
#include "GameProcess.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

D2DEngine::D2DEngine()
	:m_d2DRenderer(nullptr)
	, m_hWnd(nullptr)
	, m_hInstance(nullptr)
	, m_gameProcess(nullptr)
{
}

D2DEngine::~D2DEngine()
{
}

void D2DEngine::Initalize(HINSTANCE _hInstance, int _nCmdShow)
{
	// 윈도우 창 초기화, 메인윈도우 핸들 생성
	WindowInitalize(_hInstance, _nCmdShow);


	// D2D 랜더러 초기화
	m_d2DRenderer = new D2DRenderer();
	m_d2DRenderer->Initalize(m_hWnd);

	// GameProcess 초기화
	m_gameProcess = new GameProcess();
	m_gameProcess->Initalize(m_d2DRenderer, m_hWnd);

	// 마우스 커서 지우기
	ShowCursor(FALSE);
}

void D2DEngine::Process()
{
	MSG msg;

	while (m_gameProcess->IsGameRunning())
	{
		// 픽메세지 함수를 사용해서 메세지를 관리한다.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			// 게임 프로세스 루프
			m_gameProcess->Process();
		};
	}
}

void D2DEngine::Finalize()
{
	m_gameProcess->Finalize();
	m_d2DRenderer->Finalize();

	delete m_gameProcess;
	delete m_d2DRenderer;
}

void D2DEngine::WindowInitalize(HINSTANCE _hInstance, int _nCmdShow)
{
	constexpr wchar_t title[] = L"MidNight";

	WNDCLASS wndclass{};
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = _hInstance;
	wndclass.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = title;

	// 윈도우 클래스 등록
	RegisterClass(&wndclass);
	
	// 윈도우 창 시작좌표 (좌상단 기준)
	constexpr int left = 0;
	constexpr int top = 0;
	

	DWORD dwStyle = WS_OVERLAPPEDWINDOW; // 기본 윈도우 스타일
	DWORD dwExStyle = 0; // 기본 확장 윈도우 스타일

	// 천체 화면 모드로 변경
	dwStyle = WS_POPUP; // 팝업 스타일
	dwExStyle = WS_EX_TOPMOST; // 최상위 윈도우 스타일

	m_hWnd = CreateWindow(title, title
		, dwStyle | dwExStyle // 스타일과 확장 스타일을 결합하여 사용
		, left, top, m_screenWidth, m_screenHeight
		, NULL, NULL, _hInstance, NULL);

	//// 윈도우 창 생성
	//m_hWnd = CreateWindow(title, title
	//	, WS_OVERLAPPEDWINDOW // 창이 겹침
	//	, left, top, m_screenWidth, m_screenHeight
	//	, NULL, NULL, _hInstance, NULL);

	// 방어적코드
	assert(m_hWnd);

	ShowWindow(m_hWnd, _nCmdShow);
	UpdateWindow(m_hWnd);

	//// 화면해상도에 맞게 window 좌표계를 설정한다
	//RECT rt = { 0, 0,(long)m_screenWidth, (long)m_screenHeight };
	//AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // window 설정스타일에 맞는 rt값을 반환해준다.
	//SetWindowPos(m_hWnd, nullptr, left, top, rt.right - rt.left, rt.bottom - rt.top, 0);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
