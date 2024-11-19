#include "UserScriptsPCH.h"
#include "Chaser.h"
#include "Animation.h"
#include "Animator.h"
#include "BaseFSM.h"
#include "BaseStatement.h"
#include "GameObject.h"
#include "RendererDefine.h"

#include "ChaserStatements.h"
#include "ChasersLight.h"
#include "SpeechBubble.h"
#include "ReturnCheckPoint.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "PlayerLife.h"
#include "ClearCheck.h"
#include "FireFly.h"
#include "Chandlier.h"

Chaser::Chaser()
	: MonoBehaviour(typeid(this).name())
	, m_light(nullptr), m_fsm(nullptr)
	, m_nodeDirection(1), m_facingDirection(1)
	, m_targetNode(0), m_nodeEndIndex(0)
	, m_moveSpeed(100), m_traceSpeed(200)
	, m_chasingPlayerObj(nullptr), m_chasingInGameObj(nullptr)
	, m_isBlocked(false), m_playerLife(nullptr)
	, m_isIgnorePlayer(false), m_ignoreTimer(0.f), m_ignoreTime(3.f)
	, m_isInverse(false), m_animator(nullptr), m_bubble(nullptr), m_isBright(false)
	, m_rabbit(nullptr), m_player(nullptr), m_clearCheck(nullptr)
{

}

Chaser::~Chaser()
{
}

Component* Chaser::Clone()
{
	Chaser* clone = new Chaser();

	return clone;
}

void Chaser::SetUp(vector<Vector2> _nodes, UINT _startNode, UINT _direction, GameObject* _life, ClearCheck* _clear)
{
	GameObject* thisObj = GetGameObject();
	m_clearCheck = _clear;

	//노드 추가
	m_nodes = _nodes;
	m_nodeDirection = _direction;
	m_facingDirection = _direction;
	m_nodeEndIndex = (UINT)m_nodes.size() - 1;
	m_targetNode = (_startNode + 1) % m_nodeEndIndex;


	//위치 설정
	Transform* transform = GetComponent<Transform>();
	transform->SetPosition(m_nodes[_startNode]);

	//hp연결
	m_playerLife = _life->GetComponent<PlayerLife>();

	float frame = 1.f / 60.f;

	// 200 250
	//애니매이션 정보 생성
	m_animator = thisObj->CreateComponent<Animator>();

	static int numbering = 1;
	numbering = numbering % 3 + 1;

	SetNumbering(numbering);

	wstring name = L"maid" + std::to_wstring((numbering++)%3 +1);
	wstring walkAni = name + L"_walk";
	wstring idleAni = name + L"_question";


	m_animator->CreateAnimation2(L"chaser_Idle_Left", idleAni, Vector2(0, 0), Vector2(200, 250), Vector2(200, 0), 1.5f / 90.f, 90, FLIP_TYPE::NONE, Vector2(0.f, 250.f), 20);
	m_animator->CreateAnimation2(L"chaser_Idle_Right", idleAni, Vector2(0, 0), Vector2(200, 250), Vector2(200, 0), 1.5f / 90.f, 90, FLIP_TYPE::X_FLIP, Vector2(0.f, 250.f), 20);

	m_animator->CreateAnimation2(L"chaser_Walk_Left", walkAni, Vector2(0, 0), Vector2(200, 250), Vector2(200, 0), frame, 60, FLIP_TYPE::NONE, Vector2(0.f, 250.f), 10);
	m_animator->CreateAnimation2(L"chaser_Walk_Right", walkAni, Vector2(0, 0), Vector2(200, 250), Vector2(200, 0), frame, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 250.f), 10);


	if (m_nodeDirection == -1) m_animator->Play(L"chaser_Idle_Left", true);
	else m_animator->Play(L"chaser_Idel_Right", true);


	//버블
	m_bubble = thisObj->CreateComponent<SpeechBubble>();
	m_bubble->SetOffset(Vector2(150, 200));
	m_bubble->SetTextOffset(Vector2(-250,25));

	// 자식오브젝트로 불빛? 생성
	GameObject* child = new GameObject("chaserLight", GetManagerSet(), OBJECT_TYPE::CHASER);
	ChasersLight* light = child->CreateComponent<ChasersLight>();
	light->SetUp(this);
	GetGameObject()->AddChild(child);
	m_light = light;


	//FSM 정보 생성
	BaseFSM* fsm = thisObj->CreateComponent<BaseFSM>();

	BaseStatement* idle = new ChaserIdle(fsm, thisObj, L"MOVE");
	BaseStatement* move = new ChaserMove(fsm, thisObj, L"TRANS", transform, m_moveSpeed);
	BaseStatement* flip = new ChaserFlip(fsm, thisObj, L"IDLE");
	BaseStatement* chase = new ChaserChase(fsm, thisObj, L"SUSPICTION", transform, m_traceSpeed);
	BaseStatement* suspiction = new ChaserSuspiction(fsm, thisObj, L"RETURN", this);
	BaseStatement* trans = new ChaserTrans(fsm, thisObj, L"MOVE");
	BaseStatement* returnn = new ChaserReturn(fsm, thisObj, L"IDLE", this, m_moveSpeed);
	BaseStatement* objTrace = new ChaserObjectTrace(fsm, thisObj, L"SUSPICTION", this, m_traceSpeed);
	BaseStatement* capture = new ChaserCapture(fsm, thisObj, L"RETURN", this, m_playerLife);
	BaseStatement* gameover = new ChaserGameOver(fsm, thisObj, L"RETURN", this, m_playerLife);
	BaseStatement* rabbitGameOver = new ChaserRabbitGameOver(fsm, thisObj, L"RETURN", this, m_playerLife);

	fsm->AddState(L"IDLE", idle);
	fsm->AddState(L"MOVE", move);
	fsm->AddState(L"FLIP", flip);
	fsm->AddState(L"CHASE", chase);
	fsm->AddState(L"SUSPICTION", suspiction);
	fsm->AddState(L"TRANS", trans);
	fsm->AddState(L"RETURN", returnn);
	fsm->AddState(L"OBJ_TRACE", objTrace);
	fsm->AddState(L"CAPTURE", capture);
	fsm->AddState(L"GAMEOVER", gameover);
	fsm->AddState(L"RABBIT_GAMEOVER", rabbitGameOver);

	fsm->SetInitState(L"IDLE");
	m_fsm = fsm;

	//자식불빛에 fsm연결
	light->SetUpFSM(fsm);

	//콜라이더 생성
	BoxCollider* collider = CreateComponent<BoxCollider>();
	collider->SetScale(Vector2(90, 100));
	collider->SetTrigger(true);
}

void Chaser::SetInverse()
{
	m_animator->SetFlipType(L"chaser_Idle_Left", FLIP_TYPE::Y_FLIP);
	m_animator->SetFlipType(L"chaser_Idle_Right", FLIP_TYPE::XY_FLIP);
	m_animator->SetFlipType(L"chaser_Walk_Left", FLIP_TYPE::Y_FLIP);
	m_animator->SetFlipType(L"chaser_Walk_Right", FLIP_TYPE::XY_FLIP);

	m_light->GetComponent<TextureRenderer>()->SetYOffset(-155.f);
	m_isInverse = true;

	m_bubble->SetOffset(Vector2(150, -200));
	m_bubble->SetTextOffset(Vector2(-250, 5));
}

void Chaser::Update(float _deltaTime)
{
	// 클리어했는가
	m_isGameClear = m_clearCheck->IsClearStage();
	if (m_isGameClear)
	{
		if (m_fsm->GetCurrentStateName() == L"CHASE"
			|| m_fsm->GetCurrentStateName() == L"SUSPICTION" 
			|| m_fsm->GetCurrentStateName() == L"OBJ_TRACE")
		{
			m_fsm->StateTransistion(L"RETURN");
		}
		GetComponent<BoxCollider>()->SetActive(false);
		m_light->GetComponent<BoxCollider>()->SetActive(false);
		m_light->GetComponent<TextureRenderer>()->SetAlpha(0.f);
		
		float alpha = FMath::Lerp(m_animator->GetAlpha(), 0, _deltaTime * 3);
		m_animator->SetAlpha(alpha);
	}

	//감시자에게 플레이어가 걸린 직후 3초동안에는 무시
	if (m_isIgnorePlayer)
	{
		m_ignoreTimer += _deltaTime;
		if (m_ignoreTime < m_ignoreTimer)
		{
			m_ignoreTimer = 0.f;
			m_isIgnorePlayer = false;
		}
	}

	bool isBright = false;

	// 반딧불이가 플레이어랑 있을 때
	const vector<GameObject*>& objs1 = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::FINAL_LIGHT);
	for (auto fly : objs1)
	{
		if (fly->GetComponent<FireFly>() == nullptr)
			continue;
		
		if (fly->GetComponent<FireFly>()->IsOnPlayer())
		{
			isBright = true;
			break;
		}
	}

	// 감시자가 불켜진 샹들리에 범위 안에 있을 때
	const vector<GameObject*>& objs2 = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::INTERACTIVE_ITEM);
	for (auto chan : objs2)
	{
		if (isBright) break;
		if (chan->GetComponent<Chandlier>() == nullptr)
			continue;

		int a = 0;
		if (chan->GetComponent<Chandlier>()->GetLightOn())
		{
			if(Vector2::Distance( chan->GetComponent<Transform>()->GetPosition()
				, GetComponent<Transform>()->GetPosition()) < 2000)
				isBright = true;
		}
	}
	m_isBright = isBright;
}

void Chaser::DebugRender(D2DRenderer* _d2DRenderer)
{
	//모든 노드 표시
	Vector2 lefttop = m_nodes[0];
	Vector2 rightbottom = m_nodes[m_nodeEndIndex] + Vector2(0, 1);
	_d2DRenderer->DrawRectangle(lefttop, rightbottom, D2D1::ColorF::DarkSlateGray);

	for (int i = 0; i < m_nodes.size(); i++)
	{
		_d2DRenderer->DrawFillRectangle2(m_nodes[i] - Vector2(3, 3), m_nodes[i] + Vector2(3, 3), D2D1::ColorF::White);
	}

	// 타갯 노드 표시
	_d2DRenderer->DrawFillRectangle2(m_nodes[m_targetNode] - Vector2(3, 3), m_nodes[m_targetNode] + Vector2(3, 3), D2D1::ColorF::Orange);

	// 타겟 오브젝트 표시
	if (m_fsm->GetCurrentStateName() == L"CHASE")
	{
		wstring text;
		if (m_chasingPlayerObj->GetName() == "player") text = L" : player";
		if (m_chasingPlayerObj->GetName() == "rabbit") text = L" : rabbit";

		Vector2 pos = GetComponent<Transform>()->GetPosition() + Vector2(55, 70);
		_d2DRenderer->DrawTextW(text, pos, pos + Vector2(300, 0));
	}
}

void Chaser::OnTriggerEnter(const Collision& _collision)
{	
	//추적 상태일 때만 : 
	if (!m_isIgnorePlayer)
	{
		///플레이어와 충돌
		if (_collision.otherObject->GetName() == "player")
		{
			m_player = _collision.otherObject;
			SetIgnorePlayer(5.f);
			_collision.otherObject->GetComponent<PlayerComponent>()->GetRabbit()->GetComponent<RabbitComponent>()->ReturnToPlayer();
			m_playerLife->DicreaseLife();

			if (0 < m_playerLife->GetLife())
			{
				m_fsm->StateTransistion(L"CAPTURE");
			}
			else
			{
				m_chasingPlayerObj = _collision.otherObject;
				m_fsm->StateTransistion(L"GAMEOVER");
			}
		}

		///토끼랑 충돌
		else if (_collision.otherObject->GetName() == "rabbit")
		{
			m_rabbit = _collision.otherObject;
			//SetIgnorePlayer(5.f);
			//m_playerLife->DicreaseLife();

			if (0 < m_playerLife->GetLife())
			{
				m_fsm->StateTransistion(L"SUSPICTION");
				_collision.otherObject->GetComponent<RabbitComponent>()->ReturnToPlayer();
				//m_chasingPlayerObj = _collision.otherObject->GetComponent<RabbitComponent>()->GetMainPlayer();
			}
			else
			{
				m_chasingPlayerObj = _collision.otherObject;
				m_fsm->StateTransistion(L"RABBIT_GAMEOVER");
			}
		}


		///절벽(추격자만 충돌하는 안보이는 콜라이더를 만들어야함)
		//의심상태로 바꾼다 chaserBlocker
		//
		if (_collision.otherObject->GetName() == "chaserBlocker" /* && m_fsm->GetCurrentStateName() == L"CHASE"*/)
		{
			m_isBlocked = true;
			m_fsm->StateTransistion(L"SUSPICTION");
		}
	}
}


void Chaser::OnTriggerExit(const Collision& _collision)
{
	if (_collision.otherObject->GetName() == "chaserBlocker")
	{
		m_isBlocked = false;
	}
}


void Chaser::SetFacingDirection(int _direction)
{
	m_facingDirection = _direction;
	m_light->SetFacing(_direction);
}


void Chaser::ObjectSuspictionCallback(GameObject* _obj)
{
	if (m_fsm->GetCurrentStateName() != L"CHASE"
		&& m_fsm->GetCurrentStateName() != L"GAMEOVER"
		&& m_fsm->GetCurrentStateName() != L"CAPTURE")
	{
		m_chasingInGameObj = _obj;
		m_fsm->StateTransistion(L"OBJ_TRACE");
	}
}

