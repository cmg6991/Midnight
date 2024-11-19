#include "UserScriptsPCH.h"
#include "InteractiveItem.h"
#include "Inventory.h"

InteractiveItem::InteractiveItem()
	:MonoBehaviour(typeid(this).name())
	,m_itemType(ITEM_TYPE::NONE)
	,m_isActive(true)
	,m_isDissapear(false)
	,m_textureRenderer(nullptr)
{

}

InteractiveItem::~InteractiveItem()
{

}

Component* InteractiveItem::Clone()
{
	return nullptr;
}

void InteractiveItem::Update(float _deltaTime)
{
	if (m_isDissapear && m_textureRenderer)
	{
		float textureAlpha = m_textureRenderer->GetAlpha();
		textureAlpha -= m_dissapearSpeed * _deltaTime;
		m_textureRenderer->SetAlpha(textureAlpha);
	}
}

void InteractiveItem::Start()
{
	m_textureRenderer = GetComponent<TextureRenderer>();
}

void InteractiveItem::OnTriggerStay(const Collision& _collision)
{
	const InputManager* input = GetInputManager();

	// 상호작용 키가 눌리고 충돌한 오브젝트가 플레이어 
	// TODO :: 현재의 상태에서 플레이어 문, 토끼가 키앞에 있으면 문제가 발생가능      
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER
		&& input->IsKeyState(KEY::UP, KEY_STATE::TAP))
	{
		Interact(_collision.otherObject);
	}

}

void InteractiveItem::Interact(GameObject* _user)
{
	if (!m_isActive)
	{
		return;
	}

	switch (m_itemType)
	{
	case ITEM_TYPE::NONE:
		assert(!L"아이템 초기화를 해주세요");
		break;
	case ITEM_TYPE::KEY:
	{
		KeyProcess(_user);
	}
	break;
	case ITEM_TYPE::DOOR:
	{
		DoorProcess(_user);
	}
	break;
	default:
		break;
	}
}

void InteractiveItem::KeyProcess(GameObject* _user)
{
	Inventory* inven = _user->GetComponent<Inventory>();
	assert(inven);

	if (!inven->IsActive())
		return;

	// 사운드 플레이
	SoundManager::GetInstance()->PlaySFXSound(L"coin", 1,2);

	// 유저의 인벤토리에 접근하여 Key를 추가한다. 
	inven->PusBack(ITEM_TYPE::KEY); 

	// 한번 상호작용 이후에는 상호작용이 불가능 상태로 만든다.
	m_isActive = false;
	m_isDissapear = true  ;
	GetGameObject()->Destory(1.f);
}

void InteractiveItem::DoorProcess(GameObject* _user)
{
	Inventory* inven = _user->GetComponent<Inventory>();
    assert(inven);
	
	// 인벤토리 비활성화시 
	if (!inven->IsActive())
		return;

	// 플레이어가 키가 있는 경우 키를 사용함
	if (inven->UseItem(ITEM_TYPE::KEY))
	{
		if (SoundManager::GetInstance()->isPlayingChannel(3) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"dooropen", 1,3);
		m_isActive = false;
		m_isDissapear = true;
		GetGameObject()->Destory(1.f);
	}
	else // 플레이어가 키가 없는 경우 : 경고음 출력
	{
		if (SoundManager::GetInstance()->isPlayingChannel(4) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"gun", 1,4);
	}
}
