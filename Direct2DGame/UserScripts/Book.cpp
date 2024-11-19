#include "UserScriptsPCH.h"
#include "Book.h"
#include "Button.h"

Book::Book()
	:MonoBehaviour(typeid(this).name())
	,m_textureRenderer(nullptr)
	, m_button(nullptr)
	, m_buttonConmponent(nullptr)
	
{

}

Book::~Book()
{

}

Component* Book::Clone()
{
	Book* clone = new Book();

	return clone;
}

void Book::Start()
{
	m_textureRenderer = GetComponent<TextureRenderer>();
	//m_mySceneManager = GetSceneManager();
	m_buttonConmponent = m_button->GetComponent<Button>();
}

void Book::Update(float _deltaTime)
{
	if (m_buttonConmponent->GetSwitchOn())
	{
		m_textureRenderer->SetKey(L"bookOpen");
	}
}

void Book::Render(D2DRenderer* _d2DRenderer)
{

}

void Book::PostRender(D2DRenderer* _d2DRenderer)
{

}

void Book::DebugRender(D2DRenderer* _d2DRenderer)
{

}
