#include "UserScriptsPCH.h"
#include "InfiniteMap.h"
#include "Factory.h"

InfiniteMap::InfiniteMap()
	: MonoBehaviour(typeid(this).name())
	, m_lastObjTransform(nullptr), m_camera(nullptr), m_factory(nullptr), m_halfxSize(0.f)
	, m_initPos(), m_objType(OBJ_NAME::PILLAR), m_step(0.f), m_destroyPos(), m_createPos()
	, m_rightBoundary(0.f), m_leftBoundary(0.f)
{
	
}

InfiniteMap::~InfiniteMap()
{
	delete m_factory;
}

void InfiniteMap::SetUp(OBJ_NAME _type, Vector2 _initPos)
{
	m_factory = new Factory(GetManagerSet());
	m_camera = GetCameraManager()->GetCamera();
	
	m_objType = _type; 
	m_initPos = _initPos;

	switch (m_objType)
	{
	case OBJ_NAME::PILLAR:
		m_step = 1200.f;
		m_halfxSize = 225.f;
		break;       
	case OBJ_NAME::FOG:
		m_step = 3000.f;
		m_halfxSize = 3000.f;
		break;
	case OBJ_NAME::BACKGROUND:
		m_step = 1440.f * 6 - 1;
		m_halfxSize = 770.f * 6;
		break;
	case OBJ_NAME::ENDING_BACKGROUND:
		m_step = 1440.f - 1;
		m_halfxSize = 770.f;
		break;
	}
	m_rightBoundary = m_halfxSize + m_halfScreenWidth + m_camera->GetPosition().x;


	//처음 오브젝트 생성 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

///반복문으로 끝까지 생성하기

	do
	{
		GameObject* obj = nullptr;
		switch (m_objType)
		{
		case OBJ_NAME::PILLAR:
			obj = m_factory->CreateFrontPillar(m_initPos);
			break;
		case OBJ_NAME::FOG:
			obj = m_factory->CreateFogSystem(m_initPos, OBJECT_TYPE::FOG);
			break;
		case OBJ_NAME::BACKGROUND:
			obj = m_factory->CreateMainBackground(m_initPos);
			break;

		case OBJ_NAME::ENDING_BACKGROUND:
			obj = m_factory->CreateEndingBackground(m_initPos);
			break;
		}

		m_lastObjTransform = obj->GetComponent<Transform>();
		m_objs.push_back(obj);
		GetSceneManager()->GetCurrentScene()->RegisterObject(obj, 0);
		m_initPos.x += m_step;
	} while (m_initPos.x < m_rightBoundary);
}


void InfiniteMap::Update(float _deltaTime)
{
	m_rightBoundary = m_halfxSize + m_halfScreenWidth + m_camera->GetPosition().x;
	m_leftBoundary = m_camera->GetPosition().x -m_halfxSize - m_halfScreenWidth;

	Create();
	Destroy();
}

void InfiniteMap::Create()
{
	/// 오른쪽 바운더리 포지션과 마지막 오브젝트 포지션의 차이가 step이면 오브젝트 생성하기
	if (m_rightBoundary - m_lastObjTransform->GetPosition().x > m_step)
	{
		GameObject* obj = nullptr;
		
		switch (m_objType)
		{
		case OBJ_NAME::PILLAR:
			obj = m_factory->CreateFrontPillar(m_initPos);
			break;
		case OBJ_NAME::FOG:
			obj = m_factory->CreateFogSystem(m_initPos, OBJECT_TYPE::FOG);
			break;
		case OBJ_NAME::BACKGROUND:
			obj = m_factory->CreateMainBackground(m_initPos);
			break;
		case OBJ_NAME::ENDING_BACKGROUND:
			obj = m_factory->CreateEndingBackground(m_initPos);
			break;
		}

		m_lastObjTransform = obj->GetComponent<Transform>();
		m_objs.push_back(obj);
		GetSceneManager()->GetCurrentScene()->RegisterObject(obj, 0);
		m_initPos.x += m_step;
	}
}

void InfiniteMap::Destroy()
{
	
	///배열의 처음 오브젝트(가장 왼쪽) 바운더리를 벗어났다면 삭제
	if (GetSceneManager()->GetCurrentScene()->GetSceneName() != L"Ending")
	{
		if (0 < m_objs.size()
			&& m_objs[0]->GetComponent<Transform>()->GetPosition().x < m_leftBoundary)
		{
			m_objs[0]->Destory();
			m_objs.erase(m_objs.begin());
		}
	}
}
