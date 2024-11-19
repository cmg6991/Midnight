#include "EnginePCH.h"
#include "GameProcess.h"

GameProcess::GameProcess()
	:m_collisionManager(nullptr)
	, m_sceneManager(nullptr)
	, m_inputManager(nullptr)
	, m_timeManager(nullptr)
	, m_pathManager(nullptr)
	, m_d2DRenderer(nullptr)
	, m_hWnd(nullptr)
	, m_UIManager(nullptr)
	, m_elapsedTime(0.f)
	, m_gameRunnig(false)
	, m_showDebug(false)
	, m_screenSize{}
	, m_managerSet(nullptr)
	, m_cameraManager(nullptr)
	, m_resourceManager(nullptr)
	, m_directManager(nullptr)
{}

GameProcess::~GameProcess()
{

}

void GameProcess::Initalize(D2DRenderer* _d2DRenderer, HWND _main)
{
	// 로딩화면 
	m_pathManager = new PathManager();
	m_pathManager->Initalize();

	wstring filePath = m_pathManager->GetRelativPath(); filePath += L"\\Resource\\로딩화면.png";

	_d2DRenderer->LoadBitmapW(L"로딩화면", filePath.c_str());

	_d2DRenderer->BeginRender();

	_d2DRenderer->DrawBitmap(L"로딩화면", Vector2::Zero);
	_d2DRenderer->EndRender();
	

	// 게임 루프 활성화
	m_gameRunnig = true;

	m_d2DRenderer = _d2DRenderer;
	m_hWnd = _main;

	RECT rc{};
	// 창 클라이언트 영역 좌표
	GetClientRect(m_hWnd, &rc);

	m_screenSize = Vector2(static_cast<float>(rc.right - rc.left), static_cast<float>(rc.bottom - rc.top));

	// 매니저 메모리 공간 할당
	m_timeManager = new TimeManager();
	m_inputManager = new InputManager();
	m_collisionManager = new CollisionManager();
	m_sceneManager = new SceneManager();
	m_UIManager = new UIManager();
	m_cameraManager = new CameraManager();
	m_resourceManager = new ResourceManager();
	m_directManager = new DirectManager();

	// 매니져 집합 클래스
	m_managerSet = new ManagerSet();

	// 매니져들 연결
	m_managerSet->Initalize(m_pathManager, m_inputManager
		, m_timeManager, m_sceneManager, m_UIManager
		, m_collisionManager, m_cameraManager,m_directManager);

	/// ===================== 매니저 초기화 =====================================
	// 매니저들의 의존관계를 Initalize단계에서 표현
	m_timeManager->Initalize(m_screenSize);
	m_inputManager->Initalize(m_hWnd, m_cameraManager);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
	m_cameraManager->Initalize(m_d2DRenderer, m_screenSize, m_inputManager);
	m_UIManager->Initalize(m_sceneManager, m_managerSet);
	m_directManager->Initalize(m_screenSize, m_cameraManager);

	SoundManager::GetInstance()->Initialize();

	// 리소스 불러오기 
	m_resourceManager->Initalize(m_pathManager, m_d2DRenderer);


	/// ======================== 씬 생성 ========== =============================

	// 씬들을 생성하고 씬컨테이너를 만들고 씬매니져에게 전달한다.
	map<wstring, Scene*> sceneContainer{};
	 
	//// 씬 메모리 할당
	//Scene* ex1 = new EX1Scene();
	//Scene* ex2 = new EX2Scene();
	//Scene* ex3 = new EX3Scene();
	//Scene* ex4 = new 명기Scene();

	// MainScene
	Scene* mainScene = new MainScene();
	mainScene->SetSceneName(L"MainScene");

	// CrewScene
	Scene* crewScene = new CrewScene();
	crewScene->SetSceneName(L"CrewScene");

	// 컷씬
	Scene* startCutScene = new StartCutScene();
	startCutScene->SetSceneName(L"StartCutScene");

	// MidNightScene
	Scene* stage1 = new Stage1();
	stage1->SetSceneName(L"Stage1");

	Scene* stage2 = new Stage02();
	stage2->SetSceneName(L"Stage2");

	Scene* stage3 = new Stage03();
	stage3->SetSceneName(L"Stage3");

	Scene* ending = new EndingScene();
	ending->SetSceneName(L"Ending");

	// 씬 리스트 추가 
	sceneContainer.insert(make_pair(L"MainScene", mainScene));
	sceneContainer.insert(make_pair(L"CrewScene", crewScene));
	sceneContainer.insert(make_pair(L"StartCutScene", startCutScene));
	sceneContainer.insert(make_pair(L"Ending", ending));

	sceneContainer.insert(make_pair(L"Stage1", stage1));
	sceneContainer.insert(make_pair(L"Stage2", stage2));
	sceneContainer.insert(make_pair(L"Stage3", stage3));

	//sceneContainer.insert(std::make_pair(L"이기태", ex1));	
	//sceneContainer.insert(std::make_pair(L"김선웅", ex2));
	//sceneContainer.insert(std::make_pair(L"손서희", ex3));
	//sceneContainer.insert(std::make_pair(L"최명기", ex4));


	// 씬매니져에게 초기화과정에서 씬들과 시작씬을 지정한다.
	m_sceneManager->Initalize(_d2DRenderer, m_managerSet
		, m_collisionManager, m_directManager, sceneContainer, L"MainScene");

	// deltaTime 조정 
	m_timeManager->Update();

}

void GameProcess::Process()
{
	/// 게임에서 가장 핵심적인 부분으로 
    /// 모든 오브젝트의 함수 호출 순서를 나타내는 지점이다.
 
	float deltaTime = static_cast<float>(m_timeManager->Update());
	m_inputManager->Update();


	// 연출 시스템 업데이트
	m_directManager->Update();

	// ==================물리 처리===================
	constexpr float FIXED_DELTA_TIME = 0.02f; // 50프레임 주기
	m_elapsedTime += deltaTime;

	while (m_elapsedTime >= FIXED_DELTA_TIME)
	{
		m_elapsedTime -= FIXED_DELTA_TIME;
		m_sceneManager->FixedUpdate(FIXED_DELTA_TIME);
	}
	 
	// ========== 게임오브젝트 업데이트 ==============
	m_sceneManager->Update(deltaTime);
	m_sceneManager->LateUpdate(deltaTime);

	//  ======== 충돌처리 ============================
	m_collisionManager->Update();

	// ============= UI 이벤트 ======================	
	m_UIManager->Update();

	// ============== 카메라 이동 ===================
	m_cameraManager->Update(deltaTime);

	// ================= 랜더링 ===================
	// 랜더링은 BegineRender와 EndRender 사이에 해야한다.
	m_d2DRenderer->BeginRender();

	m_sceneManager->Render(m_d2DRenderer);

	// 카메라 효과 랜더링 
	m_cameraManager->Render(m_d2DRenderer);

	// 디버그정보 랜더링
	if (ShowDubg())
	{
		m_timeManager->DebugRender(m_d2DRenderer);
		//m_collisionManager->DebugRender(m_d2DRenderer); // AABB Tree 
		m_sceneManager->DebugRender(m_d2DRenderer);
		m_directManager->DebugRender(m_d2DRenderer);
		m_cameraManager->DebugRender(m_d2DRenderer);

		/// 시연용 키
		if (m_inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
		{
			m_sceneManager->RegisterNextScene(L"Stage1");
		}
		else if (m_inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
		{
			m_sceneManager->RegisterNextScene(L"Stage2");
		}
		else if (m_inputManager->IsKeyState(KEY::F3, KEY_STATE::TAP))
		{
			m_sceneManager->RegisterNextScene(L"Stage3");
		}
	}

	m_d2DRenderer->EndRender();

	// =============== 후속처리 =================
	// ex) 오브젝트 삭제, 추가, 씬 변경
	m_sceneManager->ProcessEvent(deltaTime);

	/// 게임을 종료
	m_gameRunnig = m_sceneManager->IsGameRun();
}

void GameProcess::Finalize()
{
	m_sceneManager->Finalize();
	m_collisionManager->Finalize();
	m_inputManager->Finalize();
	m_timeManager->Finalize();
	m_UIManager->Finalize();
	m_resourceManager->Finalize();
	m_directManager->Finalize();
	SoundManager::GetInstance()->Finalize();

	NamingManager::GetInstance()->Finalize();

	// 메모리 해제
	delete m_managerSet;
	delete m_cameraManager;
	delete m_sceneManager;
	delete m_pathManager;
	delete m_collisionManager;
	delete m_timeManager;
	delete m_inputManager;
	delete m_resourceManager;
	delete m_UIManager;
	delete m_directManager;
}

bool GameProcess::ShowDubg()
{
	if (m_inputManager->IsKeyState(KEY::F5, KEY_STATE::TAP))
	{
		m_showDebug = !m_showDebug;
	}

	return m_showDebug;
}
