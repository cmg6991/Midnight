#include "UserScriptsPCH.h"
#include "CrewScene.h"
#include "UIComponent.h"
#include "ESC.h"

CrewScene::CrewScene()
{

}

CrewScene::~CrewScene()
{

}

void CrewScene::Enter()
{
	/// 카메라 설정
	GetManagerSet()->GetCameraManager()->SetOffset(Vector2(0, 0));
	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MAINSCENE);
	GetManagerSet()->GetCameraManager()->SetCameraPos();

	GameObject* esc = new GameObject("ESC", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	esc->CreateComponent<ESC>();
	esc->CreateComponent<MouseEvent>();
	AddObject(esc);

	const float oneframe = 1.f / 60.f;

	Animator* playScene = esc->CreateComponent<Animator>();
	playScene->CreateAnimation2(L"Credit", L"Credit", Vector2::Zero, Vector2(1920.f, 1080.f), Vector2(1920.f, 0.f), oneframe, 81, FLIP_TYPE::NONE, Vector2(0.f, 1080.f), 8);
	playScene->Play(L"Credit", true);

	GameObject* escButton = new GameObject("EscButton", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	escButton->GetComponent<Transform>()->SetPosition(Vector2(-900.f,500.f));
	escButton->GetComponent<Transform>()->SetScale(Vector2(112.f, 74.f));
	escButton->CreateComponent<ESC>();
	escButton->CreateComponent<MouseEvent>();
	AddObject(escButton);
	
	Animator* playESC = escButton->CreateComponent<Animator>();
	playESC->CreateAnimation2(L"ESC", L"ESC", Vector2::Zero, Vector2(112.f, 74.f), Vector2(112.f, 0.f), oneframe, 27, FLIP_TYPE::NONE, Vector2(0.f, 74.f), 9);
	playESC->Play(L"ESC", true);

}
