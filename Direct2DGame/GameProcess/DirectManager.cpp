#include "GameProcessPCH.h"
#include "DirectManager.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "Actor.h"
#include "Letterbox.h"

DirectManager::DirectManager()
	:m_actorContainer()
	, m_currentActingOrder(0)
	, m_isStartedActing(false)
	, m_rabbitInputOn(nullptr)
	, m_playerInputOn(nullptr)
	,m_camera(nullptr)
{

}

DirectManager::~DirectManager()
{

}

void DirectManager::Initalize(Vector2 _screenSize, CameraManager* _camera)
{
	m_screenSize = _screenSize;

	m_camera = _camera;
}

void DirectManager::Finalize()
{

}

void DirectManager::Update()
{
	if (m_actingVector.empty())
		return;

	// 다음 연출을 지시한다.
	if (!m_isStartedActing &&   m_currentActingOrder < m_actingVector.size())
	{
		DiretActing();
	}	

	if (m_actingVector[m_currentActingOrder].type == ACTION_TYPE::OFF_INPUT
		|| m_actingVector[m_currentActingOrder].type == ACTION_TYPE::ON_INTPUT
		|| m_actingVector[m_currentActingOrder].type == ACTION_TYPE::LETTERBOX_OFF
		|| m_actingVector[m_currentActingOrder].type == ACTION_TYPE::CAMERA_EFFECT_ON)
	{
		m_currentActingOrder++;
		m_isStartedActing = false;
	}
}

void DirectManager::DebugRender(D2DRenderer* _renderer)
{
	// 연출이 없는 씬 
	if (m_actingVector.empty())
		return;

	wstring str = L"현재 연출 순서 : " + std::to_wstring(m_currentActingOrder) + L"\n타입 : ";
	
	switch (m_actingVector[m_currentActingOrder].type)
	{
		case ACTION_TYPE::OBJECT_MOVE:
			str += L"오브젝트 이동";
			break;
		case ACTION_TYPE::OBJECT_TALK:
		{
			// 넓은 문자열을 저장할 wstring을 선언합니다.
			wstring name;

			// 인코딩 변환기를 설정합니다.
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

			// std::string을 std::wstring으로 변환합니다.
			name = converter.from_bytes(m_actingVector[m_currentActingOrder].actorName);

			str += L" 대사\n" + name + L" : " + m_actingVector[m_currentActingOrder].talkingInfo.text;
		}	
			break;
		case ACTION_TYPE::CAMERA_MOVE:
			str += L" 카메라 이동";
			break;
		case ACTION_TYPE::CAMERA_EFFECT_ON:
			str += L"카메라 효과 추가";
			break;
		case ACTION_TYPE::LETTERBOX_OFF:
			str += L"카메라 효과 제거";
			break;
		case ACTION_TYPE::WAIT_TRIGGER:
			str += L"다음 이벤트 대기중";
			break;
		case ACTION_TYPE::OFF_INPUT:
			str += L"키 입력 비활성화";
			break;
		case ACTION_TYPE::ON_INTPUT:
			str += L"키 입력 활성화";
			break;
		default:
			break;
	}

	Vector2 leftTop{ -m_screenSize.x * 0.5f, m_screenSize.y * 0.5f - 100.f }, rightBottom{ 0.f,0.f };

	_renderer->SetCameraAffected(false);
	_renderer->DrawTextW(str, leftTop, rightBottom, D2D1::ColorF::Gold);
}

void DirectManager::Reset()
{
	m_actingVector.clear();
	m_currentActingOrder = 0;
	m_actorContainer.clear();
	m_isStartedActing = false;
	m_playerInputOn = nullptr;
	m_rabbitInputOn = nullptr;

}

void DirectManager::AddActor(GameObject* _actor)const
{
	// 숫자 인덱스가 붙어있는 이름을 가져온다
	string name =_actor->GetDebugName();
	 
	assert(m_actorContainer.find(name) == m_actorContainer.end()
	 || L"같은 배우를 두번이나 추가했습니다");

	// 배우리스트에 추가한다.
	m_actorContainer.insert(make_pair(name, _actor));
}

void DirectManager::FinishActing(int _actingOrder) const
{
	assert(m_currentActingOrder == _actingOrder
	|| L" 연출 번호가 일치하지 않습니다. ");

	++m_currentActingOrder; // 다음 연출을 진행시킨다. 
	m_isStartedActing = false;

	assert(m_currentActingOrder != m_actingVector.size()
		|| !L"다음 연출이 없습니다.");
		
}

void DirectManager::DiretActing()
{
	ActionInfomation& info = m_actingVector[m_currentActingOrder];

	switch (info.type)
	{
		case ACTION_TYPE::OBJECT_MOVE:
			break;
		case ACTION_TYPE::OBJECT_TALK:
		{
			// 해당하는 오브젝트에게 대사를 지시한다.
			auto iter= m_actorContainer.find(info.actorName);
			Actor* actor = iter->second->GetComponent<Actor>();
			actor->DirectTalking(info.talkingInfo, m_currentActingOrder);
		}
			break;
		case ACTION_TYPE::CAMERA_MOVE:
			break;
		case ACTION_TYPE::CAMERA_EFFECT_ON:
		{
			m_camera->LetterboxCamera(100.f, 50.f);
		}
			break;
		case ACTION_TYPE::LETTERBOX_OFF:
		{
			Letterbox* letterbox = dynamic_cast<Letterbox*>(m_camera->GetCurrentCameraEffect());
			assert(letterbox);
			letterbox->Close();
		}
			break;
		case ACTION_TYPE::OFF_INPUT:
		{
			// 키입력 비활성화
			*m_playerInputOn = false;
			*m_rabbitInputOn = false;
		}
			break;
		case ACTION_TYPE::ON_INTPUT:
		{
			// 키입력 활성화
			*m_playerInputOn = true;
			*m_rabbitInputOn = true;
		}
			break;
		default:
			break;
	}

	m_isStartedActing = true;
}

void DirectManager::AddTalkingAction(const string& _actorName
	, const wstring& _imageKey, const wstring& _text
	, ColorF _color /*= ColorF::Black*/, float _outTempo /*= 0.1f*/) const
{
	ActionInfomation act{}; 
	act.type = ACTION_TYPE::OBJECT_TALK;
	act.actorName = _actorName;
	act.talkingInfo.imageKey = _imageKey;
	act.talkingInfo.outputTempo = _outTempo;
	act.talkingInfo.text = _text;
	act.talkingInfo.textColor = _color;

	PushBackActionInfomation(act);
}

void DirectManager::AddMovingAction(const string& _actorName, Vector2 _distance, float _moveSpeed)
{

}

void DirectManager::PushBackActionInfomation(ActionInfomation _info) const
{
	 int actingOrder = static_cast<int>(m_actingVector.size());
	 _info.actingOrder = m_currentActingOrder;

	 m_actingVector.push_back(_info);
}

void DirectManager::WaitNextTrigger()const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::WAIT_TRIGGER;

	PushBackActionInfomation(act);
}


void DirectManager::OnLetterBox() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::CAMERA_EFFECT_ON;
	act.cameraEffectType = CAMERA_EFFECT_TYPE::LETTERBOX;
	
	PushBackActionInfomation(act);
}

void DirectManager::OffLetterBox() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::LETTERBOX_OFF;

	PushBackActionInfomation(act);
}

void DirectManager::OffInput() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::OFF_INPUT;

	PushBackActionInfomation(act);
}

void DirectManager::OnInput() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::ON_INTPUT;

	PushBackActionInfomation(act);
}

void DirectManager::StartStage1Scripts() const 
{	
	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);

	OffInput(); // 0

	// 일반 연출 1번 
	AddTalkingAction("rabbit", L"bubble (20)", L"저택을 따뜻하고 밝게 \n만들어 보자!",rabbitColor);
	AddTalkingAction("player", L"bubble (2)", L"좋아!",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"그런데 여긴 너무\n 춥고 습해...",playerColor);
	AddTalkingAction("player", L"bubble (3)", L"[안개] 때문인가?",playerColor);
	AddTalkingAction("rabbit", L"bubble (18)", L"방법을 찾아보자!",rabbitColor);

	OnInput();

	WaitNextTrigger(); // 7

	// 첫번째 상호작용 연출
	AddTalkingAction("player", L"bubble (1)", L"!", playerColor);
	AddTalkingAction("player", L"bubble (5)", L"[커튼]을 치니까 \n[안개]가 사라졌어", playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"모든 [커튼]을 열어서\n [안개]를 없애자!", rabbitColor);

	WaitNextTrigger(); // 11

	OffInput();

	// 일반 연출 2번 
	AddTalkingAction("player", L"bubble (1)", L"!",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"이제야 공기가 맑아진\n 거 같아",playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"커튼을 여니까 훨씬 낫네",rabbitColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"2층으로 내려가보자!",rabbitColor);

	WaitNextTrigger(); // 스테이지 클리어 17

	// 이미지 띄우기
}

void DirectManager::StartStage2Scripts() const
{

	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);

	// 일반 연출 3번 - 2번 스테이지(2층) 시작할 때 
	OffInput();
	AddTalkingAction("player", L"bubble (3)", L"(오들 오들)", playerColor);
	AddTalkingAction("player", L"bubble (4)", L"으.. 여기는 추워", playerColor);
	AddTalkingAction("rabbit", L"bubble (17)", L"저기 봐!", rabbitColor);
	AddTalkingAction("rabbit", L"bubble (18)", L"[고드름]이야!",rabbitColor);
	AddTalkingAction("player", L"bubble (5)", L"[고드름]에 닿으면 \n너무 차갑겠다",playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[고드름]을 녹일 방법이\n 없을까?",rabbitColor);
	OnInput();

	WaitNextTrigger(); // 8

	// 첫번째 상호작용 연출
	AddTalkingAction("player", L"bubble (1)", L"!", playerColor);
	AddTalkingAction("player", L"bubble (5)", L"[촛불]을 켜니까\n 고드름이 녹았네", playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[촛불]을 켜서 여기를 \n따뜻하게 만들자!", rabbitColor);

	WaitNextTrigger(); // 12

	OffInput();
	// 일반 연출 4번 - 2번 스테이지(2층) 끝날 때
	AddTalkingAction("player", L"bubble (1)", L"!",playerColor);
	AddTalkingAction("player", L"bubble (3)", L"이제 춥지 않아",playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"복도가 따뜻해졌어",rabbitColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"이제 고드름 때문에\n 위험하지도 않고!",rabbitColor);
	AddTalkingAction("player", L"bubble (1)", L":)",playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"1층으로 내려가보자!",rabbitColor);

	WaitNextTrigger(); // 스테이지 클리어 20
}

void DirectManager::StartStage3Scripts() const
{
	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);

	OffInput();

	// 일반 연출 5번 - 3스테이지(1층) 시작할 때
	AddTalkingAction("rabbit", L"bubble (18)", L"드디어 1층이다!",rabbitColor);
	AddTalkingAction("player", L"bubble (5)", L"너무 어두워서\n 잘 안보여",playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"로비가 이렇게\n 어두워서야!",rabbitColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"불을 켜야 할 거 같은데?",rabbitColor);
	AddTalkingAction("player", L"bubble (4)", L"저기 [샹들리에]가 있어!",playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[샹들리에]를 켜려면\n 어떻게 할까?",rabbitColor);

	OnInput();

	WaitNextTrigger(); // 8

	// 첫번째 상호작용 연출
	AddTalkingAction("player", L"bubble (1)", L"!", playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"[샹들리에]가 켜졌어", rabbitColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[버튼]으로 [샹들리에]를\n 키자!", rabbitColor);

	WaitNextTrigger();

	OffInput(); //13

	// 일반 연출 6번 - 3스테이지(1층) 끝날 떄
	AddTalkingAction("player", L"bubble (1)", L"!",playerColor);
	AddTalkingAction("rabbit", L"bubble (17)", L"밝아졌다!",rabbitColor);
	AddTalkingAction("player", L"bubble (3)", L"이젠 잘 보여",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"저택이 이렇게 넓고\n 예쁜 곳이었구나",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"이렇게 다 둘러본 건 \n오늘이 처음이야",playerColor);
	AddTalkingAction("rabbit", L"bubble (16)", L":)",rabbitColor);
	AddTalkingAction("player", L"bubble (2)", L"고마워",playerColor);

	WaitNextTrigger(); //21

	
}

void DirectManager::EndingScripts() const
{
	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);
	WaitNextTrigger();
	AddTalkingAction("player", L"bubble (3)", L"드디어 도착했다!", playerColor);
	AddTalkingAction("player", L"bubble (3)", L"저기 봐! 문이야!", playerColor);
	WaitNextTrigger();
	OffInput(); 
	AddTalkingAction("rabbit", L"bubble (20)", L"이제 바깥 구경을\n할 수 있겠어!", rabbitColor);
	AddTalkingAction("player", L"bubble (2)", L"응응!", playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"오늘 재미있었어. 그치?", rabbitColor);
	AddTalkingAction("player", L"bubble (5)", L"응! 이렇게 노는 건\n 처음이야!", playerColor);
	AddTalkingAction("player", L"bubble (4)", L"저택도 따뜻해졌고!", playerColor);
	AddTalkingAction("player", L"bubble (3)", L"토끼야 고마워!", playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"아니야! 네가 한 거야!", rabbitColor);
	WaitNextTrigger();

}

