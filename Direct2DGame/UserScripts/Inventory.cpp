#include "UserScriptsPCH.h"
#include "Inventory.h"

Inventory::Inventory()
	:MonoBehaviour(typeid(this).name())
	,m_itemList{}
	,m_active(false)
{

}

Inventory::~Inventory()
{

}

Component* Inventory::Clone()
{
	Inventory* clone = new Inventory();
	clone->m_itemList = m_itemList;

	return clone;
}

bool Inventory::UseItem(ITEM_TYPE _type)
{
	auto iter = m_itemList.begin();

	// 아이템리스트를 순회한다. 
	while (iter != m_itemList.end())
	{
		// 같은 아이템 타입이이면 사용한다. 
		if (*iter == _type)
		{
			m_itemList.erase(iter);
			return true; 
		}
		++iter;
	}

	// 아이템 사용 실패
	return false;
}

void Inventory::PusBack(ITEM_TYPE _type)
{
	m_itemList.push_back(_type);
}

void Inventory::PassItemList(list<ITEM_TYPE>& _passed)
{
	_passed.clear();

	_passed = m_itemList;

	m_itemList.clear();
}
