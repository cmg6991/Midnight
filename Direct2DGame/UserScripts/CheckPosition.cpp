#include "UserScriptsPCH.h"
#include "CheckPosition.h"
#include "Chaser.h"

CheckPosition::CheckPosition()
	:MonoBehaviour(typeid(this).name())
	,m_numbering(0)
{

	m_offset = Vector2(0.f, 25.f);
}

CheckPosition::~CheckPosition()
{

}

Component* CheckPosition::Clone()
{
	return nullptr;
}

void CheckPosition::Start()
{
	m_numbering = GetComponent<Chaser>()->GetNumbering();
}

void CheckPosition::Render(D2DRenderer* _d2DRenderer)
{
	Vector2 cameraPos = GetCameraManager()->GetCamera()->GetPosition();

	Vector2 maidPos = GetComponent<Transform>()->GetPosition();
	Vector2 cMaidPos = GetCameraManager()->WorldToCamera(maidPos);

	_d2DRenderer->SetCameraAffected(false);

	wstring keyUp = L"maidUpPos" + std::to_wstring(m_numbering);
	wstring keyDown = L"maidDownPos" + std::to_wstring(m_numbering);
	if (Flip() && cameraPos.y <= -250.f)
	{
		cMaidPos.y = 500.f - m_offset.y;
		_d2DRenderer->DrawBitmap(keyUp, cMaidPos, 0.f,0.1f,FLIP_TYPE::NONE);
	}
	else if (!Flip() && cameraPos.y >= -760.f)
	{
		cMaidPos.y = -500.f;
		cMaidPos += m_offset;
		_d2DRenderer->DrawBitmap(keyDown, cMaidPos, 0.f, 0.1f, FLIP_TYPE::NONE);
	}

	_d2DRenderer->SetCameraAffected(true);
}
