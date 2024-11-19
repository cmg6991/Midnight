#pragma once

class CameraManager;
/// <summary>
/// Actor, Camera들을 가지고 연출을 담당하는 매니져이다. 
/// 
/// 
/// 2023.8.9 16:32 gitae
/// </summary>
class DirectManager
{
public:
	DirectManager();
	~DirectManager();

	void Initalize(Vector2 _screenSize, CameraManager* _camera);
	void Finalize();
	void Update();
	void DebugRender(D2DRenderer* _renderer);

	// 씬변경시 호출
	void Reset();

public:
	void AddActor(GameObject* _actor)const ;
	
	// 매니져에게 자신의 연출이 끝났음을 알린다.
	void FinishActing(int _actingOrder) const;

	int GetCurrentActingOrder() const { return m_currentActingOrder; }

public:
	// Stage1의 연출 스크립트
	void StartStage1Scripts() const;
	void StartStage2Scripts() const;
	void StartStage3Scripts() const;
	void EndingScripts() const;

	// 플레이어의 키입력 변수를 받는다
	void SetPlayerInputOn(bool* _playerInputOn) const { m_playerInputOn = _playerInputOn; }
	// 토끼의 키입력 변수를 받는다. 
	void SetRabbitInputOn(bool* _rabbitInputOn) const { m_rabbitInputOn = _rabbitInputOn; }

private:
	void DiretActing();
	void AddTalkingAction(const string& _actorName
		, const wstring& _imageKey, const wstring& _text
		, ColorF _color = ColorF::Black, float _outTempo = 0.1f) const;
	void AddMovingAction(const string& _actorName, Vector2 _distance, float _moveSpeed);

	void PushBackActionInfomation(ActionInfomation _info) const;
	void WaitNextTrigger()const;

	void OnLetterBox()const;
	void OffLetterBox()const;
	void OffInput()const;
	void OnInput()const;

private:
	CameraManager* m_camera;

	// 플레이어와 토끼의 Key입력을 OnOff한다.
	mutable bool* m_playerInputOn;
	mutable bool* m_rabbitInputOn;

	Vector2 m_screenSize;

	mutable vector<ActionInfomation> m_actingVector;
	mutable int m_currentActingOrder; // 현재 연출 번호
	mutable bool m_isStartedActing; // 현재 연출이 시작한지   
	mutable map<string, GameObject*> m_actorContainer; // 연출에 필요한 게임오브젝트들 
};

