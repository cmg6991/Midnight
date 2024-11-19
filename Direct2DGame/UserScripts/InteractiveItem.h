#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 상호작용 아이템
/// 
/// 2023.8.8 14:18 gitae
/// </summary>
class InteractiveItem :
    public MonoBehaviour
{
public:
    InteractiveItem();
    ~InteractiveItem();
    Component* Clone() override;
    
private:
    void Update(float _deltaTime) override;
    void Start() override;

    void OnTriggerStay(const Collision& _collision) override;

public:
    bool IsActive() const { return m_isActive; }
    void SetActive(bool val) { m_isActive = val; }
    ITEM_TYPE GetItemType() const { return m_itemType; }
    void SetItemType(ITEM_TYPE _type) { m_itemType = _type; }

    /// 상호작용 - 아이템 타입에따라서 다르게 상호작용한다. 
    void Interact(GameObject* _user);

private:
    void KeyProcess(GameObject* _user);
    void DoorProcess(GameObject* _user);

private:
    TextureRenderer* m_textureRenderer;
    ITEM_TYPE m_itemType; // 아이템 타입
    bool m_isActive; // 상호작용 가능한 상태 표시
    bool m_isDissapear; // 사라지는 중인지

    const float m_dissapearSpeed = 1.f; // 투명화 속도
};

