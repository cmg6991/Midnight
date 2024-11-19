#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 플레이어의 인벤토리 컴포넌트 
/// 플레이어가 소유하고 있는 아이템을 관리한다. 
///  
/// 간단한 리스트로 아이템을 관리한다.
/// 
/// 2023.8.8 14:26 gitae
/// </summary>
class Inventory :
    public MonoBehaviour
{
public:
    Inventory();
    ~Inventory();
    Component* Clone() override;

    bool IsActive() const { return m_active; }
    void SetActive(bool val) { m_active = val; }
public:
    // 인벤토리를 반환한다.
    list<ITEM_TYPE>& GetInventory() { return m_itemList; }

    // 사용에 성공하면 true, 사용에 실패하면 false를 반환한다.
    bool UseItem(ITEM_TYPE _type);

    // 아이템을 인벤토리에 추가한다. 
    void PusBack(ITEM_TYPE _type);

    // 아이템을 전달한다. 
    void PassItemList(list<ITEM_TYPE>& _passed);

private:    
    list<ITEM_TYPE> m_itemList; // 인벤토리의 아리템 리스트

    bool m_active; // 아이템 리스트 활성화 상태 확인 

};

