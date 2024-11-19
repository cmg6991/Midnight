#pragma once
#include "Component.h"
class BaseStatement;

/// <summary>
/// 
/// 일단 모든상태 -> 모든 상태로 전이 가능하게 만들었다. 나중에 수정할 예정
/// 
/// 23.08.07 손서희
/// </summary>


/// FSM의 기본 추상 클래스 
class BaseFSM : public Component
{
///생성자와 소멸자ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
public:
	BaseFSM();
	~BaseFSM();

	Component* Clone() override;
	void SetInitState(wstring _name);


///맴버 함수 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
public:
	virtual void Update(float _deltaTime);
	virtual void DebugRender(D2DRenderer* _d2DRenderer);

	void StateTransistion(wstring _key);
	void AddState(wstring _key, BaseStatement* _state) { m_allTransitions.insert({ _key, _state }); }
	wstring GetCurrentStateName();

private:
	BaseStatement* FindState(wstring _key);


///맴버 변수 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
private:
	map<wstring, BaseStatement*> m_allTransitions;  //모든 Transition 정보
	BaseStatement* m_currentState;					//현재 Trasnsition
};

