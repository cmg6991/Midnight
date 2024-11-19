#pragma once
#include <BaseStatement.h>
class Transform;
class Component;
class Chaser;
class SpeechBubble;
class PlayerLife;



enum class CHASER_STATE
{
	IDLE,		//
	TRANS,		// 다음 이동을 결정
	MOVE,		// 이동
	FLIP,		// 방향 전환
	CHASE,		// 플레이어 추격
	SUSPICION,	// 의심
	RETURN,		// 원래 루트로 복귀
	//STAY		// 방향전환할때 필요하면 넣기
	OBJ_TRACE,	// 오브젝트 의심
	CAPTURE,	// 생명이 남은 상태에서 플레이어를 붙잡았을 때
	GAMEOVER,	// 생명이 남지 않은 상태에서 플레이어를 붙잡았을 때
	RABBIT_GAMEOVER //토끼 상태로 게임오버
};


/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserIdle : public BaseStatement
{
public:
	ChaserIdle(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~ChaserIdle();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

private:
	float m_waitingTime;

};


/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserMove : public BaseStatement
{
public:
	ChaserMove(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _moveSpeed);
	~ChaserMove();
	
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

	void setTargetPos(Vector2 _pos) { m_targetPos = _pos; }

private:
	Chaser* m_chaser;
	Animator* m_animator;
	Transform* m_transform;
	Vector2 m_targetPos;
	Vector2 m_lastPos;
	float m_moveSpeed;
	Vector2 m_currentPos;
	int m_direction;
};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserFlip : public BaseStatement
{
public:
	ChaserFlip(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~ChaserFlip();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

private:
	Chaser* m_chaser;
	Animator* m_animator;

};


/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
class ChaserChase : public BaseStatement
{
public:
	ChaserChase(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _chaseSpeed);
	~ChaserChase();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

	void SetTargetObj(GameObject* _obj) { m_targetObj = _obj; }

private:
	Chaser* m_chaser;
	GameObject* m_targetObj;
	Transform* m_targetTransform;
	Transform* m_transform;
	Animator* m_animator;
	SpeechBubble* m_speechBubble;
	float m_chaseSpeed;
};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserSuspiction : public BaseStatement
{
public:
	ChaserSuspiction(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser);
	~ChaserSuspiction();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

private:
	Chaser* m_chaser;
	Animator* m_animator;
	SpeechBubble* m_speechBubble;

	int m_count;
};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
class ChaserTrans : public BaseStatement
{
///생성자와 소멸자
public:
	ChaserTrans(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~ChaserTrans();


///멤버 함수
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///멤버 변수
private:


};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserReturn : public BaseStatement
{
///생성자와 소멸자
public:
	ChaserReturn(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _moveSpeed);
	~ChaserReturn();


///멤버 함수
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///멤버 변수
private:
	Chaser* m_chaser;
	Vector2 m_targetPos;
	Animator* m_animator;
	Transform* m_transform;
	float m_moveSpeed;
	Vector2 m_lastPos;
};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserObjectTrace : public BaseStatement
{
///생성자와 소멸자
public:
	ChaserObjectTrace(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _traceSpeed);
	~ChaserObjectTrace();


///멤버 함수
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///멤버 변수
private:
	Chaser* m_chaser;
	Vector2 m_targetPos;
	Animator* m_animator;
	float m_moveSpeed;
	Transform* m_transform;
	int m_direction;
	SpeechBubble* m_speechBubble;

	float minExitPosX;
	float maxExitPosX;
};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
class ChaserCapture : public BaseStatement
{
///생성자와 소멸자
public:
	ChaserCapture(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life);
	~ChaserCapture();


///멤버 함수
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///멤버 변수
private:
	Chaser* m_chaser;
	PlayerLife* m_Playerlife;
	int m_direction;
	SpeechBubble* m_speechBubble;
};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserGameOver : public BaseStatement
{
	///생성자와 소멸자
public:
	ChaserGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life);
	~ChaserGameOver();


	///멤버 함수
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


	///멤버 변수
private:
	Chaser* m_chaser;
	PlayerLife* m_Playerlife;
	int m_direction;
	SpeechBubble* m_speechBubble;
	GameObject* m_player;

	Transform* m_playerTransform;
	Transform* m_thisTransform;

	int m_act;
};

/// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class ChaserRabbitGameOver : public BaseStatement
{
	///생성자와 소멸자
public:
	ChaserRabbitGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life);
	~ChaserRabbitGameOver();


	///멤버 함수
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


	///멤버 변수
private:
	Chaser* m_chaser;
	PlayerLife* m_Playerlife;
	int m_direction;
	SpeechBubble* m_speechBubble;
	GameObject* m_rabbit;

	Transform* m_rabbitTransform;
	Transform* m_thisTransform;

	int m_act;
};