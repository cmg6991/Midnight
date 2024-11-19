#include "UserScriptsPCH.h"
#include "Webtoon.h"

Webtoon::Webtoon()
	:MonoBehaviour(typeid(this).name())
	,m_currentIndex(1)
	,m_isFinish(true)
{
	m_chaserPos = Vector2{ 500.f,0.f };
	m_girlPos = Vector2{ 0.f, 1000.f };
}

Webtoon::~Webtoon()
{

}

Component* Webtoon::Clone()
{


	return nullptr; 
}

void Webtoon::Update(float _deltaTime)
{
    const InputManager* input = GetInputManager();

	if ( (input->IsKeyState(KEY::LMOUSE,KEY_STATE::TAP)||input->IsKeyState(KEY::SPACE, KEY_STATE::TAP) ) 
		&& m_currentIndex != 4 && m_currentIndex != 5 && m_currentIndex !=6 && m_currentIndex != 9
		&& m_currentIndex != 11)
	{
		++m_currentIndex;
	}

	if (m_currentIndex == 4)
	{
		// 0 ~ 1000 위치까지 이동 
		const float chaserSpeed = 500.f;

		m_chaserPos.x += chaserSpeed * _deltaTime;	

		// 집사 들썩들썩

		// 내려기가기
		if (m_isDown)
		{
			m_chaserPos.y -= chaserSpeed * _deltaTime * 0.25f;
		} 
		else // 올라가기 
		{
			m_chaserPos.y += chaserSpeed * _deltaTime * 0.5f;
		}
		if (m_chaserPos.y >= 50.f)
		{
			m_isDown = true;
		}
		else if (m_chaserPos.y <= 0.f)
		{
			m_isDown = false;
		}


		if (m_chaserPos.x >= 2000.f)
		{
			++m_currentIndex;
		}
	}
	else if (m_currentIndex == 5)
	{
		m_cameraPos.y += _deltaTime * 500.f;

		if (m_cameraPos.y >= 1240.f)
		{
			m_cameraPos.y = 1240.f;
			++m_currentIndex;
		}
	}
	else if (m_currentIndex == 6) // 소녀 떨어지기
	{
		// 0 ~ 1000 위치까지 이동 
		const float girlSpeed = 1200.f;

		m_girlPos.x = -200.f;
		m_girlPos.y -= girlSpeed * _deltaTime;

		if (m_girlPos.y <= -250.f)
		{
			m_girlPos.y = -250.f;
			++m_currentIndex;
		}
	}
	else if (m_currentIndex == 9) // 카메라로 이동 
	{
		// 0 ~ 1000 위치까지 이동 
		const float cameraSpeed = 500.f;

		m_cameraPos.x += cameraSpeed * _deltaTime;

		if (m_cameraPos.x >= 1000.f)
		{
			m_cameraPos.x = 1000.f;
			++m_currentIndex;
		}
	}
	else if (m_currentIndex == 11) //
	{

		// 0 ~ 1000 위치까지 이동 
		const float girlSpeed = 500.f;

		m_girlPos.x += girlSpeed * _deltaTime;

		// 플레이어 들썩들썩

		// 내려기가기
		if (m_isDown)
		{
			m_girlPos.y -= girlSpeed * _deltaTime * 0.25f;
		}
		else // 올라가기 
		{
			m_girlPos.y += girlSpeed * _deltaTime * 0.5f;
		}
		if (m_girlPos.y >= 50.f)
		{
			m_isDown = true;
		}
		else if (m_girlPos.y <= 0.f)
		{
			m_isDown = false;
		}


		if (m_girlPos.x >= 500.f)
		{
			GetCameraManager()->FadeOutCamera(3.f,false);
		}
		if (m_girlPos.x >= 2000.f)
		{
			GetSceneManager()->RegisterNextScene(L"Stage1");
		}
	}


}

void Webtoon::Render(D2DRenderer* _d2DRenderer)
{
	Vector2 position = GetComponent<Transform>()->GetPosition();

	const Vector2 girlScale(0.7f, 0.7f);

	if (m_currentIndex == 0)
	{ 
		// 아무것도 안나온다 
	}
	else if (m_currentIndex == 1)
	{
		_d2DRenderer->DrawBitmap(L"S1_01", position);
	}
	else if (m_currentIndex == 2)
	{
		_d2DRenderer->DrawBitmap(L"S1_01", position);
		_d2DRenderer->DrawBitmap(L"S1_02", position);
	}
	else if (m_currentIndex == 3)
	{
		_d2DRenderer->DrawBitmap(L"S1_01", position);
		_d2DRenderer->DrawBitmap(L"S1_02", position);
		_d2DRenderer->DrawBitmap(L"S1_03", position);
	}
	else if (m_currentIndex == 4) // 천장달려있음
	{
		Vector2 pos = position;
		pos.x += 960.f;
		pos.y -= 540.f;

		_d2DRenderer->DrawBitmap(L"S1_04", pos);
		_d2DRenderer->DrawBitmap(L"S1_05", position + m_chaserPos);
	}
	else if (m_currentIndex == 5) // 카메라가 아래로 점점 내려간다.
	{
		Vector2 pos = position;
		pos.x += 960.f;
		pos.y -= 540.f;

		_d2DRenderer->DrawBitmap(L"S1_04", pos + m_cameraPos);
	}
	else if (m_currentIndex == 6) // 소녀가 천장에서 내려옴 
	{
		Vector2 pos = position;
		pos.x += 960.f;
		pos.y += 700.f;

		_d2DRenderer->DrawBitmap(L"S1_04", pos );
		_d2DRenderer->DrawBitmap(L"S1_06", pos + m_girlPos,0.f,1.f,FLIP_TYPE::NONE,girlScale);
	}
	else if (m_currentIndex == 7) // 소녀가 천장에서 내려옴 
	{
		Vector2 pos = position;
		pos.x += 960.f;
		pos.y += 700.f;

		_d2DRenderer->DrawBitmap(L"S1_04", pos);
		_d2DRenderer->DrawBitmap(L"S1_06", pos + m_girlPos , 0.f, 1.f, FLIP_TYPE::NONE, girlScale);
	}
	else
	{
		Vector2 offset = Vector2(-500.f, -400.f);

		if (m_currentIndex == 8) // 소녀와 토끼가 나옴 
		{
			m_cameraPos = Vector2::Zero;
			Vector2 pos = position;
			pos.x += 960.f;
			pos.y += 700.f;
			_d2DRenderer->DrawBitmap(L"S1_04", pos);
			_d2DRenderer->DrawBitmap(L"S1_07", pos + offset, 0.f, 1.f, FLIP_TYPE::NONE, girlScale);
		}
		else if (m_currentIndex == 9)
		{
			Vector2 pos = position;
			pos.x += 960.f;
			pos.y += 700.f;

			_d2DRenderer->DrawBitmap(L"S1_04", pos - m_cameraPos);
			_d2DRenderer->DrawBitmap(L"S1_07", pos - m_cameraPos+ offset, 0.f, 1.f, FLIP_TYPE::NONE, girlScale);

		}
		else if (m_currentIndex == 10)
		{
			m_girlPos = Vector2::Zero;

			Vector2 pos = position;
			pos.x += 960.f;
			pos.y += 700.f;
			_d2DRenderer->DrawBitmap(L"S1_04", pos - m_cameraPos);
			_d2DRenderer->DrawBitmap(L"S1_07", pos - m_cameraPos+ offset, 0.f, 1.f, FLIP_TYPE::NONE, girlScale);

		}
		else if (m_currentIndex == 11) // 마지막 플레이어 이동 
		{
			Vector2 pos = position;
			pos.x += 960.f;
			pos.y += 700.f;

			_d2DRenderer->DrawBitmap(L"S1_04", pos - m_cameraPos);
			_d2DRenderer->DrawBitmap(L"S1_07", pos - m_cameraPos + m_girlPos+ offset, 0.f, 1.f, FLIP_TYPE::NONE, girlScale);
		}

	}


	// 가림막 랜더링
	_d2DRenderer->DrawBitmap(L"cinemascope", position);
}
