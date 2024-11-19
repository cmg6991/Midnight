#pragma once


class BaseFSM;
class GameObject;

/// <summary>
/// 
/// 23.08.07 槳憮��
/// </summary>


/// FSM曖 и 鼻鷓蒂 薑曖ж朝 蹺鼻 贗楚蝶
class BaseStatement
{
///儅撩濠諦 模資濠 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
public:
	BaseStatement(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~BaseStatement() {};

/// 補幗 л熱 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
public:
	virtual void Update(float _deltaTime) {};

	virtual void OnStateEnter() {};
	virtual void OnStateExcution() {};
	virtual void OnStateExit() {};

	wstring getNext()			{ return m_nextState; }
	void SetNext(wstring _next)	{ m_nextState = _next; }

	bool isLoop()						{ return m_isLoop; }
	void setLoop(bool _arg)				{ m_isLoop = _arg; }

	wstring getName()					{ return m_name; }


/// 補幗 滲熱 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
protected:
	wstring m_name;  //蛤幗梵辨戲煎 餌辨脾 
	BaseFSM* m_fsm;
	GameObject* m_gameObject;

	float m_timer;
	bool m_isLoop;
	wstring m_nextState;

};





