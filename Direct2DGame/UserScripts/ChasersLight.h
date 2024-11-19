#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 
/// 추적자가 따라오다 절벽 만나면 더이상 안따라오게 하는거 
/// 대충 야매로 만들었는데
/// 나중에 버그 생길수도 있을 것 같다..
/// 그때 기태오빠가 말한 거리측정 방식으로 바꿔야겠다
/// 
/// 23.08.08 손서희
/// </summary>

class Chaser;


///추적자의 자식 오브젝트로 감시범위 및 불빛 스프라이트를 포함
class ChasersLight : public MonoBehaviour
{
public:
	ChasersLight();
	~ChasersLight();
	
	Component* Clone();
	void SetUp(Chaser* _parent);
	void SetUpFSM(BaseFSM* _fsm) { m_fsm = _fsm; }

public:
	void Update(float _deltaTime);
	void DebugRender(D2DRenderer* _d2DRenderer);

	void OnTriggerEnter(const Collision& _collision);
	void OnTriggerStay(const Collision& _collision);
	void OnTriggerExit(const Collision& _collision);

	void Filp();
	void SetFacingLeft();
	void SetFacingRight();
	void SetFacing(int _direction);



private:
	Vector2 m_offset;
	Transform* m_transform;
	TextureRenderer* m_texture;
	BoxCollider* m_collider;
	Chaser* m_chaserComp;
	BaseFSM* m_fsm;
	const InputManager* m_inputManager;

	bool m_isCollidingPlayer;

	Vector2 m_lastRabbitPos;

	bool m_isBright;
	const Vector2 m_defaultColliderSize = Vector2(350, 240);
	const Vector2 m_defaultColliderOffset = Vector2(0, -80);

	const Vector2 m_brightColliderSize = Vector2(490,240);
	Vector2 m_brightColliderOffset = Vector2(75, -80);

	Vector2 m_imgOffset = Vector2( -70.f,0.f);
};

