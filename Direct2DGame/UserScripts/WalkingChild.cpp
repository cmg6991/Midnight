#include "UserScriptsPCH.h"
#include "WalkingChild.h"

WalkingChild::WalkingChild()
	: MonoBehaviour(typeid(this).name()), m_transform(nullptr)
{

}

WalkingChild::~WalkingChild()
{

}

void WalkingChild::Start()
{
	m_transform = GetGameObject()->GetComponent<Transform>();

	//애니메이터 생성
	Animator* anim = CreateComponent<Animator>();
	anim->CreateAnimation2(L"playerWalk", L"girl_walk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f)
		, 1.f / 60.f, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 10);
	anim->Play(L"playerWalk", true);
	GetComponent<Transform>()->SetPosition(Vector2(-750,-400));
}

void WalkingChild::Update(float _deltaTime)
{
	Vector2 pos = m_transform->GetPosition();
	pos.x = pos.x + _deltaTime * 200.f;
	m_transform->SetPosition(pos);
}
