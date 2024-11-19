#pragma once
#include <MonoBehaviour.h>
/// <summary>
/// 
/// FSM을 써봤는데 이게맞나
/// 그냥 코드가 어디파일에 써있냐 차이같은데!!
/// 
/// 상태를 Enum으로 쓰면 편할거 같은데 
/// 그렇게 하려면 BaseFSM을 상속받은 무언가를 만들어 써야한다
/// 
/// 2023.08.08 손서희
/// </summary>

class ChasersLight;
class BaseFSM;
class PlayerLife;
class SpeechBubble;
class ClearCheck;

///플래이어를 감시하는 녀석
class Chaser : public MonoBehaviour
{
///생성자와 소멸자 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
public:
	Chaser();
	~Chaser();
	Component* Clone();

	void SetUp(vector<Vector2> _nodes, UINT _startNode, UINT _direction, GameObject* _life, ClearCheck* _clear);
	void SetInverse();

	int GetNumbering() const { return m_numbering; }
	void SetNumbering(int val) { m_numbering = val; }
	/// 맴버 함수 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
public:
	void Update(float _deltaTime);
	void DebugRender(D2DRenderer* _d2DRenderer);
	void OnTriggerEnter(const Collision& _collision);
	void OnTriggerExit(const Collision& _collision);

	void FlipNodeDirection() { m_nodeDirection *= -1; }
	int GetNodeDirection() { return m_nodeDirection; }

	void SetFacingDirection(int _direction);
	void FlipFacingDirection() { m_facingDirection *= -1; }
	int GetFacingDirection() { return m_facingDirection; }	

	UINT GetNodeEndIndex() { return m_nodeEndIndex; }
	void SetTargetNode(UINT _node) { m_targetNode = _node; }
	UINT GetTargetNode() { return m_targetNode; }
	Vector2 GetTargetPos() { return m_nodes[m_targetNode]; }
	ChasersLight* GetLight() { return m_light; }
	
	GameObject* GetChasingPlayerObj() { return m_chasingPlayerObj; }
	void SetChasingPlayerObj(GameObject* _obj) { m_chasingPlayerObj = _obj; }

	GameObject* GetChasingInGameObj() { return m_chasingInGameObj; }
	void SetChasingInGameObj(GameObject* _obj) { m_chasingInGameObj = _obj; }

	GameObject* GetPlayerObj() { return m_player; }
	GameObject* GetRabbitObj() { return m_rabbit; }

	bool IsBlocked() { return m_isBlocked; }

	void ObjectSuspictionCallback(GameObject* _obj);
	void SetIgnorePlayer(float _time) { m_isIgnorePlayer = true; m_ignoreTime = _time; }
	bool IsIngoringPlayer() { return m_isIgnorePlayer; }

	bool IsInverse() { return m_isInverse; }
	bool IsBright() { return m_isBright; }
	bool IsGameClear() { return m_isGameClear; }

///맴버 변수 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
protected:
	vector<Vector2> m_nodes;	// 이동 경로 ( 왼 -> 오 정렬 )
	UINT m_nodeEndIndex;		// 노드의 마지막 인덱스
	UINT m_targetNode;			// 다음번에 이동할 노드
	
	int m_nodeDirection;		// 현재 노드 이동 방향 (1 : ->) (-1 : <-)
	int m_facingDirection;		// 현재 바라보는 방향

	float m_moveSpeed;			// 배회 속도
	float m_traceSpeed;			// 추적 속도

	SpeechBubble* m_bubble;		// 말풍선
	Animator* m_animator;		// 애니메이터
	ChasersLight* m_light;		// 자식오브젝트의 light 컴포넌트
	BaseFSM* m_fsm;				// fsm
	GameObject* m_chasingPlayerObj;
	GameObject* m_chasingInGameObj;
	PlayerLife* m_playerLife;
	ClearCheck* m_clearCheck;

	bool m_isBlocked;			// 벽에 막혀있는가(절벽 앞인가)

	bool m_isIgnorePlayer;		// 플레이어를 무시할 시간
	float m_ignoreTimer;		
	float m_ignoreTime;			

	bool m_isInverse;			// 역중력 하녀인가
	bool m_isBright;			// 반딧불이 or 샹들리에 상태인가
	bool m_isGameClear;

	int m_numbering;
	GameObject* m_player;
	GameObject* m_rabbit;
};


//FireFly
//Chandlier