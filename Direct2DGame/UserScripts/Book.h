#pragma once
#include "MonoBehaviour.h"

class Button;
class Book : public MonoBehaviour
{
public:
	Book();
	~Book();

	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;
	/// 가장 기본적인 랜더링 이벤트
	void Render(D2DRenderer* _d2DRenderer) override;

	void PostRender(D2DRenderer* _d2DRenderer) override;
	/// 디버그 전용 랜더링 함수 F5를 온오프
	void DebugRender(D2DRenderer* _d2DRenderer) override;
	void SetButton(GameObject* val) { m_button = val; }

private:
	GameObject* m_button;

	// 받아온 컴포넌트
	//BoxCollider* m_boxCollider;
	TextureRenderer* m_textureRenderer;
	Button* m_buttonConmponent;


};

