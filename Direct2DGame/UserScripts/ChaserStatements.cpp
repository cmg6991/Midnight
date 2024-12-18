#include "UserScriptsPCH.h"
#include "ChaserStatements.h"
#include "BaseFSM.h"
#include "BaseStatement.h"
#include "Chaser.h"
#include "ChasersLight.h"
#include "SpeechBubble.h"
#include "PlayerComponent.h"
#include "RabbitComponent.h"

/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										Idle 
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

ChaserIdle::ChaserIdle(BaseFSM* _fsm, GameObject* _obj, wstring _nextState)
	: BaseStatement(_fsm, _obj, _nextState), m_waitingTime(1)
{
	m_name = L"IDLE";
}

ChaserIdle::~ChaserIdle()
{
}

void ChaserIdle::Update(float _deltaTime)
{

}

void ChaserIdle::OnStateEnter()
{
	// 檜翕п撿 й 寞щ擊 唸薑???

	//闊衛 棻擠 鼻鷓煎 霞殮
	m_fsm->StateTransistion(m_nextState); //move
}

void ChaserIdle::OnStateExit()
{

}


/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										寡��
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天


ChaserMove::ChaserMove(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _moveSpeed)
	: BaseStatement(_fsm, _obj, _nextState)
{
	m_name = L"MOVE";
	m_chaser = m_gameObject->GetComponent<Chaser>();
	m_animator = m_gameObject->GetComponent<Animator>();
	
	m_transform = _transform;
	m_moveSpeed = _moveSpeed;
}

ChaserMove::~ChaserMove()
{
}

void ChaserMove::Update(float _deltaTime)
{
	//檜翕衛霽
	m_lastPos = m_transform->GetPosition();
	m_currentPos = m_lastPos + Vector2(m_direction , 0) * _deltaTime * m_moveSpeed;
	m_transform->SetPosition(m_currentPos);

	//и 喻萄 檜翕檜 部釭賊 idle 鼻鷓煎 霞殮
	if( (m_lastPos.x <= m_targetPos.x && m_currentPos.x >= m_targetPos.x)
		|| m_lastPos.x >= m_targetPos.x && m_currentPos.x <= m_targetPos.x)
		m_fsm->StateTransistion(m_nextState); //idle
}

void ChaserMove::OnStateEnter()
{
	m_targetPos = m_chaser->GetTargetPos();
	m_direction = m_chaser->GetNodeDirection();

	//渠晦 擁棲衙檜暮 寞щ 瞪��
	if (m_chaser->GetNodeDirection() == -1)
	{
		m_animator->Play(L"chaser_Walk_Left", true);
		m_chaser->GetLight()->SetFacingLeft();
	}
	else
	{
		m_animator->Play(L"chaser_Walk_Right", true);
		m_chaser->GetLight()->SetFacingRight();
	}
}

void ChaserMove::OnStateExit()
{

}

/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										蹺問
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

ChaserChase::ChaserChase(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _chaseSpeed)
	: BaseStatement(_fsm, _obj, _nextState)
	, m_transform(_transform), m_chaseSpeed(_chaseSpeed)
	, m_chaser(nullptr), m_targetObj(nullptr), m_targetTransform(nullptr), m_speechBubble(nullptr)
{
	m_name = L"CHASE";
	m_chaser = m_gameObject->GetComponent<Chaser>();
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
	m_animator = m_gameObject->GetComponent<Animator>();
}

ChaserChase::~ChaserChase()
{
}

void ChaserChase::Update(float _deltaTime)
{
	//夥塭獐 寞щ擊 唸薑ж堅, ん雖暮擊 機等檜お п遽棻.
	Vector2 targetPos = m_targetTransform->GetPosition();
	Vector2 pos = m_transform->GetPosition();
	
	// 橾薑 彰嬪 頂縑 氈擊 陽
	if (abs(pos.x - targetPos.x) < 5)
	{

	}

	//Ы溯檜橫陛 螃艇薹縑 氈擊 陽
	else if (pos.x < targetPos.x)
	{
		m_chaser->SetFacingDirection(1);
		m_animator->Play(L"chaser_Walk_Right", true);
		pos.x += m_chaseSpeed * _deltaTime;
	}

	//Ы溯檜橫陛 豭薹縑 氈擊 陽
	else
	{
		m_chaser->SetFacingDirection(-1);
		m_animator->Play(L"chaser_Walk_Left", true);
		pos.x -= m_chaseSpeed * _deltaTime;
	}

	m_transform->SetPosition(pos);
}

void ChaserChase::OnStateEnter()
{
	//顫啃 螃粽薛お蒂 陛螳螞棻
	m_targetObj = m_chaser->GetChasingPlayerObj();
	assert(m_targetObj != nullptr || !L"評塭陞 螃粽薛お陛 null歜");
	m_targetTransform = m_targetObj->GetComponent<Transform>();

	//蜓Ё摹
	if (m_chaser->IsInverse())
	{
		m_speechBubble->SetBackground(L"bubble (6)");
	}
	else
	{
		m_speechBubble->SetBackground(L"bubble (1)");
	}
	m_speechBubble->SetXOffset(0);
	m_speechBubble->ShowText(L"!");
}

void ChaserChase::OnStateExit()
{
	//蜓Ё摹
	m_speechBubble->SetXOffset(150);
	m_speechBubble->CloseText();
}


/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										曖褕
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
ChaserSuspiction::ChaserSuspiction(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser)
	: BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_count(0), m_animator(nullptr)
{
	m_name = L"SUSPICTION";
	m_animator = m_gameObject->GetComponent<Animator>();
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserSuspiction::~ChaserSuspiction()
{
}

void ChaserSuspiction::Update(float _deltaTime)
{
	//謝辦 舒葬廓
	m_timer += _deltaTime;
	if (0.5f < m_timer)
	{
		m_count++;
		m_timer -= 0.5f;
		
		//驍轎
		if (m_count == 4)
		{
			m_fsm->StateTransistion(m_nextState); //idle
		}
		//夥塭爾朝 寞щ 夥紱晦
		else
		{
			m_chaser->FlipFacingDirection();

			//渠晦 擁棲衙檜暮 寞щ 瞪��
			if (m_chaser->GetFacingDirection() == -1)
			{
				m_animator->Play(L"chaser_Idle_Left", true);
				m_chaser->GetLight()->SetFacing(-1);
			}
			else
			{
				m_animator->Play(L"chaser_Idle_Right", true);
				m_chaser->GetLight()->SetFacing(1);
			}
		}
	}
}

void ChaserSuspiction::OnStateEnter()
{
	m_timer = 0.f;
	m_count = 0;

	///蜓Ё摹 嗥辦晦
	m_speechBubble->SetXOffset(0);
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (6)");
	else						m_speechBubble->SetBackground(L"bubble (1)");
	m_speechBubble->ShowText(L"?");

	//渠晦 擁棲衙檜暮 寞щ 瞪��
	if (m_chaser->GetFacingDirection() == -1)
	{
		m_animator->Play(L"chaser_Idle_Left", true);
		m_chaser->GetLight()->SetFacing(-1);
	}
	else
	{
		m_animator->Play(L"chaser_Idle_Right", true);
		m_chaser->GetLight()->SetFacing(1);
	}
}

void ChaserSuspiction::OnStateExit()
{
	///蜓Ё摹 橈擁晦
	m_speechBubble->SetXOffset(150);
	m_speechBubble->CloseText();
}

/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										寞щ瞪��
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

ChaserFlip::ChaserFlip(BaseFSM* _fsm, GameObject* _obj, wstring _nextState)
	: BaseStatement(_fsm, _obj, _nextState), m_animator(nullptr), m_chaser(nullptr)
{
	m_name = L"FLIP";
	m_chaser = m_gameObject->GetComponent<Chaser>();
	m_animator = m_gameObject->GetComponent<Animator>();
}

ChaserFlip::~ChaserFlip()
{
}

void ChaserFlip::Update(float _deltaTime)
{

}

void ChaserFlip::OnStateEnter()
{
	// 寞щ 瞪��
	m_chaser->FlipNodeDirection();

	//渠晦 擁棲衙檜暮 寞щ 瞪��
	if (m_chaser->GetNodeDirection() == -1)
	{
		m_animator->Play(L"chaser_Idle_Left", true);
		m_chaser->GetLight()->SetFacing(-1);
	}
	else
	{
		m_animator->Play(L"chaser_Idle_Right", true);
		m_chaser->GetLight()->SetFacing(1);
	}

	//闊衛 Idle 鼻鷓煎 霞殮
	m_fsm->StateTransistion(m_nextState); //idle
}

void ChaserFlip::OnStateExit()
{
}

/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										棻擠 檜翕 唸薑
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

ChaserTrans::ChaserTrans(BaseFSM* _fsm, GameObject* _obj, wstring _nextState)
	: BaseStatement(_fsm, _obj, _nextState)
{
	m_name = L"TRANS";
}

ChaserTrans::~ChaserTrans()
{
}

void ChaserTrans::Update(float _deltaTime)
{
}

void ChaserTrans::OnStateEnter()
{
	// 喻萄 鼻鷓, 寞щ擊 嫡嬴諦 寞щ瞪��, 傳朝 寡�虞� 瞪檜衛霽(next state煤 夥羞棻)
	Chaser* chaser = m_gameObject->GetComponent<Chaser>();
	int dir = chaser->GetNodeDirection();
	UINT curNode = chaser->GetTargetNode();
	UINT endNode = chaser->GetNodeEndIndex();

	if ((/* <- */  dir == -1 && curNode == 0)
		|| (/* -> */  dir == 1 && curNode == endNode))
		m_nextState = L"FLIP";
	else
	{
		m_nextState = L"MOVE";

		// targetNode蒂 滲唳衛鑑棻
		if (curNode != endNode)
			chaser->SetTargetNode(curNode + 1);
		else
			chaser->SetTargetNode(0);
	}

	//闊衛 棻擠 鼻鷓煎 霞殮
	m_fsm->StateTransistion(m_nextState); //move or flip
}

void ChaserTrans::OnStateExit()
{
}

/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										犒敝
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

ChaserReturn::ChaserReturn(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _moveSpeed)
	: BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_moveSpeed(_moveSpeed)
{
	m_name = L"RETURN";
	m_animator = m_gameObject->GetComponent<Animator>();
	m_transform = m_gameObject->GetComponent<Transform>();
}

ChaserReturn::~ChaserReturn()
{ }

void ChaserReturn::Update(float _deltaTime)
{
	// 顫啃ん鍔蒂 щп 勘橫除棻
	Vector2 pos = m_transform->GetPosition();
	
	
	if (pos.x < m_targetPos.x) //陛撿й 夠檜 螃艇薹
	{
		m_chaser->SetFacingDirection(1);
		m_animator->Play(L"chaser_Walk_Right", true);
		pos.x += m_moveSpeed * _deltaTime;

		if (m_lastPos.x <= m_targetPos.x && m_targetPos.x <= pos.x) //紫雜ц棻賊, 
		{
			// 菴縑 move陛 澀 腎紫煙 擒除曖 嬪纂 offset擊 遽棻.
			if (m_chaser->GetNodeDirection() == 1)  pos.x = m_targetPos.x - 0.1f;
			else									pos.x = m_targetPos.x + 0.1f;

			//棻擠 鼻鷓煎 霞殮
			m_fsm->StateTransistion(m_nextState); //idle
		}
	}
	else //陛撿й 夠檜 豭薹
	{
		m_chaser->SetFacingDirection(-1);
		m_animator->Play(L"chaser_Walk_Left", true);
		pos.x -= m_moveSpeed * _deltaTime;

		if (m_lastPos.x >= m_targetPos.x && m_targetPos.x >= pos.x) //紫雜ц棻賊, 
		{
			// 菴縑 move陛 澀 腎紫煙 擒除曖 嬪纂 offset擊 遽棻.
			if (m_chaser->GetNodeDirection() == 1)  pos.x = m_targetPos.x - 0.1f;
			else									pos.x = m_targetPos.x + 0.1f;

			//棻擠 鼻鷓煎 霞殮
			m_fsm->StateTransistion(m_nextState); //idle
		}
	}
	m_transform->SetPosition(pos);
	m_lastPos = pos;
}

void ChaserReturn::OnStateEnter()
{
	m_targetPos = m_chaser->GetTargetPos();
	m_lastPos = m_transform->GetPosition();
}

void ChaserReturn::OnStateExit()
{
}

/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										螃粽薛お 蹺瞳..?
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

ChaserObjectTrace::ChaserObjectTrace(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _traceSpeed)
	:BaseStatement(_fsm, _obj, _nextState), m_moveSpeed(_traceSpeed), m_chaser(_chaser), m_speechBubble(nullptr)
{
	m_name = L"OBJ_TRACE";
	m_animator = m_gameObject->GetComponent<Animator>();
	m_transform = m_gameObject->GetComponent<Transform>();
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserObjectTrace::~ChaserObjectTrace()
{
}

void ChaserObjectTrace::Update(float _deltaTime)
{
	// 顫啃ん鍔蒂 щп 勘橫除棻
	Vector2 pos = m_transform->GetPosition();
	pos.x += m_direction * m_moveSpeed * _deltaTime;
	m_transform->SetPosition(pos);

	// 驍轎 褻勒
	if( minExitPosX <= pos.x  && pos.x <= maxExitPosX )
		m_fsm->StateTransistion(m_nextState); //suspiction
}

void ChaserObjectTrace::OnStateEnter()
{
	m_targetPos = m_chaser->GetChasingInGameObj()->GetComponent<Transform>()->GetPosition();
	minExitPosX = m_targetPos.x - 1.f;
	maxExitPosX = m_targetPos.x + 1.f;
	
	// 寞щ擊 �挫恉炾� 擁棲衙檜暮 夥紱晦
	Vector2 pos = m_transform->GetPosition();
	if (pos.x < m_targetPos.x) //陛撿й 夠檜 螃艇薹
	{
		m_chaser->SetFacingDirection(1);
		m_animator->Play(L"chaser_Walk_Right", true);
		m_direction = 1;
	}
	else
	{
		m_chaser->SetFacingDirection(-1);
		m_animator->Play(L"chaser_Walk_Left", true);
		m_direction = -1;
	}

	// 蜓Ё摹
	m_speechBubble->SetXOffset(0);
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (6)");
	else						m_speechBubble->SetBackground(L"bubble (1)");
	m_speechBubble->ShowText(L"?");
}

void ChaserObjectTrace::OnStateExit()
{
	m_speechBubble->CloseText();
}


/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										儅貲檜 陴擎 鼻鷓煎 Ы溯檜楝蒂 濩懊擊 陽
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
ChaserCapture::ChaserCapture(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life)
	:BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_Playerlife(_life), m_direction(1), m_speechBubble(nullptr)
{
	m_name = L"CAPTURE";
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserCapture::~ChaserCapture()
{
}

void ChaserCapture::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (1.f < m_timer)
	{
		m_speechBubble->SetXTextOffset(-250);
		m_speechBubble->SetXOffset(150);
		
		
		if(m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (9)");
		else						m_speechBubble->SetBackground(L"bubble (4)");
		m_speechBubble->ShowText(L"橡艇 寞戲煎 給嬴陛撮蹂!");
	}
	if (2.f < m_timer)
	{
		m_fsm->StateTransistion(m_nextState);
	}
}

void ChaserCapture::OnStateEnter()
{
	// 褻濛 旎雖
	bool* playerInput = m_chaser->GetPlayerObj()->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = false;
	bool* rabbitInput = m_chaser->GetPlayerObj()->GetComponent<PlayerComponent>()->GetRabbit()->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = false;

	m_timer = 0.f;
	m_direction = m_chaser->GetFacingDirection();
	if (m_direction == 1) m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Right", true);
	else				  m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Left", true);
	
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (8)");
	else						m_speechBubble->SetBackground(L"bubble (3)");
	
	m_speechBubble->SetXTextOffset(-250);
	m_speechBubble->SetXOffset(100);
	
	m_speechBubble->ShowText(L"夤擎 嬪яп蹂");

	//羹檜憮 塭檜お 楠渦葭 莖晦
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(0.f);
}

void ChaserCapture::OnStateExit()
{
	// 褻濛 旎雖 п薯
	bool* playerInput = m_chaser->GetChasingPlayerObj()->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = true;
	bool* rabbitInput = m_chaser->GetChasingPlayerObj()->GetComponent<PlayerComponent>()->GetRabbit()->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = true;

	// 蜓Ё摹 莖晦
	m_speechBubble->CloseText();

	//羹檜憮 塭檜お 楠渦葭 麵晦
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(1.f);

}


/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										Ы溯檜橫 鼻鷓煎 啪歜螃幗
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

ChaserGameOver::ChaserGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life)
	:BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_Playerlife(_life), m_direction(1), m_speechBubble(nullptr), m_player(nullptr)
{
	m_name = L"GAMEOVER";
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserGameOver::~ChaserGameOver()
{

}

void ChaserGameOver::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (1.f < m_timer && m_act == 0)
	{
		if (m_chaser->IsInverse()) 
		{
			m_speechBubble->SetTextOffset(Vector2(-250, 5));
			m_speechBubble->SetBackground(L"bubble (8)");
			m_speechBubble->SetXOffset(100);
		}
		else
		{
			m_speechBubble->SetTextOffset(Vector2(-250, 25));
			m_speechBubble->SetBackground(L"bubble (3)");
			m_speechBubble->SetXOffset(100);
		}
		m_speechBubble->ShowText(L"等溥棻 萄萵啪蹂.");
		m_act++;
	}
	if (2.f < m_timer)
	{
		if (m_act == 1)
		{
			//蜓Ё摹 殘晦, 蘋詭塭
			m_speechBubble->CloseText();
			m_gameObject->GetManagerSet()->GetCameraManager()->FadeOutCamera(3.f, false);
			
			//擁棲衙檜暮 夥紱晦
			m_gameObject->GetComponent<Animator>()->Play(L"chaser_Walk_Left", true);
			
			m_act++;
		}

		//務晦 
		Vector2 thisPos = m_gameObject->GetComponent<Transform>()->GetPosition();
		thisPos.x = thisPos.x - _deltaTime * 100.f;
		m_thisTransform->SetPosition(thisPos);

		Vector2 playerPos = m_playerTransform->GetPosition();
		if (playerPos.x - thisPos.x > 20)
		{
			m_player->GetComponent<PlayerComponent>()->SetRightDirection(true);
			playerPos.x = playerPos.x - _deltaTime * 100.f;
			m_playerTransform->SetPosition(playerPos);
		}

	}
	if (5.f < m_timer)
	{
		// 蝶纔檜雖 營衛濛
		wstring name = m_gameObject->GetManagerSet()->GetSceneManager()->GetCurrentScene()->GetSceneName();
		m_gameObject->GetManagerSet()->GetSceneManager()->RegisterNextScene(name);
	}
}

void ChaserGameOver::OnStateEnter()
{	
	m_player = m_chaser->GetChasingPlayerObj();
	
	// 褻濛 旎雖
// 	m_player->GetComponent<BoxCollider>()->SetActive(false);
// 	m_player->GetComponent<RigidBody>()->~RigidBody();
	bool* playerInput = m_player->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = false;
	bool* rabbitInput = m_player->GetComponent<PlayerComponent>()->GetRabbit()->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = false;


	//嬪纂 嫡嬴螃晦	
	m_playerTransform = m_player->GetComponent<Transform>();
	m_thisTransform = m_gameObject->GetComponent<Transform>();

	//滲熱 蟾晦��
	m_timer = 0.f;
	m_act = 0;

	//擁棲衙檜暮 薑雖
	m_direction = m_chaser->GetFacingDirection();
	if (m_direction == 1) m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Right", true);
	else				  m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Left", true);

	//蜓Ё摹
	if (m_chaser->IsInverse())
	{
		m_speechBubble->SetBackground(L"bubble (10)");
		m_speechBubble->SetTextOffset(Vector2(-250, 28));
	}
	else 
	{
		m_speechBubble->SetBackground(L"bubble (5)");
		m_speechBubble->SetTextOffset(Vector2(-250, 48));
	}						
	m_speechBubble->ShowText(L"嬴陛噢!\n嬴霜紫 寰 菟橫陛樟橫蹂?");

	//羹檜憮 塭檜お 楠渦葭 莖晦
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(0.f);
}

void ChaserGameOver::OnStateExit()
{

}


/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
///										饜郭 鼻鷓煎 啪歜螃幗
/// 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
ChaserRabbitGameOver::ChaserRabbitGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life)
	:BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_Playerlife(_life), m_direction(1), m_speechBubble(nullptr), m_rabbit(nullptr)
{
	m_name = L"RABBIT_GAMEOVER";
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserRabbitGameOver::~ChaserRabbitGameOver()
{

}

void ChaserRabbitGameOver::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (1.f < m_timer && m_act == 0)
	{
		m_speechBubble->CloseText();
		m_act++;
	}
	if (2.f < m_timer)
	{
		if (m_act == 1)
		{
			//蜓Ё摹 殘晦, 蘋詭塭
			m_speechBubble->CloseText();
			m_gameObject->GetManagerSet()->GetCameraManager()->FadeOutCamera(3.f, false);

			//擁棲衙檜暮 夥紱晦
			m_gameObject->GetComponent<Animator>()->Play(L"chaser_Walk_Left", true);

			m_act++;
		}

		//務晦 
		Vector2 thisPos = m_gameObject->GetComponent<Transform>()->GetPosition();
		thisPos.x = thisPos.x - _deltaTime * 100.f;
		m_thisTransform->SetPosition(thisPos);

		Vector2 rabbitPos = m_rabbitTransform->GetPosition();
		if (rabbitPos.x - thisPos.x > 0)
		{
			rabbitPos.x = rabbitPos.x - _deltaTime * 100.f;
			m_rabbitTransform->SetPosition(rabbitPos);
		}

	}
	if (5.f < m_timer)
	{
		// 蝶纔檜雖 營衛濛
		wstring name = m_gameObject->GetManagerSet()->GetSceneManager()->GetCurrentScene()->GetSceneName();
		m_gameObject->GetManagerSet()->GetSceneManager()->RegisterNextScene(name);
	}
}

void ChaserRabbitGameOver::OnStateEnter()
{
	m_rabbit = m_chaser->GetChasingPlayerObj();

	// 褻濛 旎雖
	// m_rabbit->GetComponent<BoxCollider>()->SetActive(false);
	// m_rabbit->GetComponent<RigidBody>()->~RigidBody();
	bool* rabbitInput = m_rabbit->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = false;
	bool* playerInput = m_rabbit->GetComponent<RabbitComponent>()->GetMainPlayer()->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = false;


	//嬪纂 嫡嬴螃晦	
	m_rabbitTransform = m_rabbit->GetComponent<Transform>();
	m_thisTransform = m_gameObject->GetComponent<Transform>();

	//滲熱 蟾晦��
	m_timer = 0.f;
	m_act = 0;

	//擁棲衙檜暮 薑雖
	m_direction = m_chaser->GetFacingDirection();
	if (m_direction == 1) m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Right", true);
	else				  m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Left", true);

	//蜓Ё摹
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (10)");
	else						m_speechBubble->SetBackground(L"bubble (5)");
	m_speechBubble->ShowText(L"檣⑽檜 謁 釭諦氈雖?");

	//羹檜憮 塭檜お 楠渦葭 莖晦
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(0.f);

	//饜郭 擁棲衙檜暮 薑雖?
	m_rabbit->GetComponent<Animator>()->SetTimeRatio(0.000001f);
}

void ChaserRabbitGameOver::OnStateExit()
{

}