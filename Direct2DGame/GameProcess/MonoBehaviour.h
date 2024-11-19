#pragma once
#include "Component.h"

class InputManager;

struct Collision;

/// <summary>
/// UserScript의 추상클래스이다
///
/// </summary>
class MonoBehaviour abstract :
    public Component
{
public:
    MonoBehaviour(string _name);
    ~MonoBehaviour() override;

    /// 생성 관련 함수
    void Start() override {};
    void Finalize() override {};

    /// 이벤트 관련함수
    void Update(float _deltaTime) override {};
    void FixedUpdate(float _fixedDeltaTime) override {};
    void PreRender(D2DRenderer* _d2DRenderer) override {};
    void Render(D2DRenderer* _d2DRenderer) override {};
    void PostRender(D2DRenderer* _d2DRenderer) override {};

    /// 충돌 관련 함수
    void OnCollisionStay(const Collision& _collision) override {};
    void OnCollisionEnter(const Collision& _collision) override {};
    void OnCollisionExit(const Collision& _collision) override {};
    void OnTriggerExit(const Collision& _collision)override {};
	void OnTriggerStay(const Collision& _collision) override {};
	void OnTriggerEnter(const Collision& _collision) override {};

    /// 마우스 입력 함수
    virtual void OnMouse() {};
    virtual void OnMouseUp() {};
    virtual void OnMouseDown() {};
    virtual void OnMouseClicked() {};
};

