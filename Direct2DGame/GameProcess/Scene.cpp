#include "GameProcessPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "PathManager.h"
#include "FileManager.h"
#include "ManagerSet.h"
#include "SceneManager.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "CircleCollider.h"
#include "CollisionManager.h"
#include "GameObjectSort.h" // 게임 오브젝트 정렬 알고리즘
#include "MouseCursor.h"


Scene::Scene()
	:m_d2DRenderer(nullptr)
	,m_managerSet(nullptr)
	,m_objectVector{}
	,m_nextScene(L"NONE")
	,m_addObjectList{}
	,m_scneneManager(nullptr)
{
}

Scene::~Scene()
{
}

void Scene::Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet, SceneManager* _sceneManager)
{
	m_scneneManager = _sceneManager;
	m_managerSet = _managerSet;
	m_d2DRenderer = _d2DRenderer;

	AddMouse();
}

void Scene::Finalize()
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		DestoryGroupObject(static_cast<OBJECT_TYPE>(i)); 
	}
}

void Scene::Render(D2DRenderer* _d2DRenderer)
{
	SortObjBySortingLayer();

	assert(_d2DRenderer);

	/// 랜더링은 부모 오브젝트가 자식 오브젝트의 랜더링까지 담당한다.
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			bool isCameraAffectedObject = iter->IsCameraAffected();

			_d2DRenderer->SetCameraAffected(isCameraAffectedObject);

			iter->PreRender(_d2DRenderer);
		}

		for (auto iter : m_objectVector[i])
		{
			bool isCameraAffectedObject = iter->IsCameraAffected();

			_d2DRenderer->SetCameraAffected(isCameraAffectedObject);

			iter->Render(_d2DRenderer);
		}

		for (auto iter : m_objectVector[i])
		{
			bool isCameraAffectedObject = iter->IsCameraAffected();

			_d2DRenderer->SetCameraAffected(isCameraAffectedObject);

			iter->PostRender(_d2DRenderer);
		}
	}
}

void Scene::ProcessEvent(float _deltaTime)
{
	/// 씬변경 이벤트
	if (m_nextScene != L"NONE")
	{
		m_scneneManager->ChangeScene(m_nextScene);
		return;
	}

	/// 오브젝트 삭제관리 
	/// 오브젝트 풀링도 고민해봐야?
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		auto iter = m_objectVector[i].begin();

		while (iter != m_objectVector[i].end())
		{
			GameObject* object = (*iter);
			OBJECT_STATE state = object->GetObjectState();

			if (state == OBJECT_STATE::DESTORY)
			{
				// 오브젝트 삭제처리
				object->Finalize();
				delete object;
				iter = m_objectVector[i].erase(iter);
			}
			else 
			{
				if (state == OBJECT_STATE::TO_BE_DESTORYED && object->GetDestroyTime() <= 0.f)
				{
					// 다음 프레임이 오브젝트 메모리 해제
					// 자식 오브젝트들만 삭제한다, 부모는 삭제하지 않는다.
					queue<GameObject*> q;
					q.push(object);
					while (!q.empty())
					{
						GameObject* tmp = q.front();
						tmp->SetObjectState(OBJECT_STATE::DESTORY);
						
						vector<GameObject*>& children = tmp->GetChildren();
						for (int i = 0; i < static_cast<int>(children.size()); ++i)
						{
							q.push(children[i]);
						}
						q.pop();
					}
				}
				++iter;
			}
		}
	}

	/// 오브젝트 추가 관리 
	auto iter = m_addObjectList.begin();

	while (iter != m_addObjectList.end())
	{
		iter->delayTime -= _deltaTime;
		if (iter->delayTime <= 0.f)
		{
			AddObject(iter->object);

			// 스타트 함수 호출
			iter->object->Start();
			iter = m_addObjectList.erase(iter);
		}
		else
			++iter;
	}
}


void Scene::SortObjectVector()
{
	// 랜더링을 위한 정렬
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		std::sort(m_objectVector[i].begin(), m_objectVector[i].end(), SortVectorFunction);
	}
}

void Scene::SortObjBySortingLayer()
{
	// 랜더링을 위한 정렬
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		std::sort(m_objectVector[i].begin(), m_objectVector[i].end(), SortLayerFuction);
	}
}

void Scene::AddMouse()
{
	GameObject* mouse = new GameObject("mouse", GetManagerSet(), OBJECT_TYPE::MOUSE);
	mouse->CreateComponent<MouseCursor>();
	AddObject(mouse);
}

void Scene::Start()
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto object : m_objectVector[i])
		{
			object->Start();
		}
	}
}

void Scene::RegisterObject(GameObject* _object, float _delayTime) const
{
	/// 추가해야하는 오브젝트 정보
	AddObjectInfomation info{};
	info.delayTime = _delayTime;
	info.object = _object;

	m_addObjectList.push_back(std::move(info));
}

void Scene::RegisterNextScene(const wstring& _sceneName) const
{
	m_nextScene = _sceneName;
}

void Scene::DubugRender(D2DRenderer* _d2DRenderer)
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			bool isCameraAffectedObject = iter->IsCameraAffected();

			_d2DRenderer->SetCameraAffected(isCameraAffectedObject);

			iter->DebugRender(_d2DRenderer);
		}
	}
}

void Scene::Exit()
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		DestoryGroupObject(static_cast<OBJECT_TYPE>(i));
	}

	/// 추가하는 오브젝트 목록 초기화
	for (auto& info : m_addObjectList)
	{
		GameObject* object = info.object;
		if (object != nullptr)
		{
			delete object;
		}
	}
	m_addObjectList.clear();

	// 다음씬 지정 해제
	m_nextScene = L"NONE";
}

void Scene::FixedUpdate(float _fixedDeltaTime)
{
	if (m_scneneManager->IsPause())
	{
		for (int i = static_cast<int>(OBJECT_TYPE::BACK_UI); i < static_cast<int>(OBJECT_TYPE::END); ++i)
		{
			for (auto iter : m_objectVector[i])
			{
				iter->FixedUpdate(_fixedDeltaTime);
			}
		}
	}
	else
	{
		for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
		{
			for (auto iter : m_objectVector[i])
			{
				iter->FixedUpdate(_fixedDeltaTime);
			}
		}
	}
}

void Scene::Update(float _deltaTime)
{
	if (m_scneneManager->IsPause())
	{
		for (int i = static_cast<int>(OBJECT_TYPE::BACK_UI); i < static_cast<int>(OBJECT_TYPE::END); ++i)
		{
			for (auto iter : m_objectVector[i])
			{
				iter->Update(_deltaTime);
			}
		}
	}
	else
	{
		for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
		{
			for (auto iter : m_objectVector[i])
			{
				iter->Update(_deltaTime);
			}
		}
	}
}

void Scene::LateUpdate(float _deltaTime)
{
	if (m_scneneManager->IsPause())
	{
		for (int i = static_cast<int>(OBJECT_TYPE::BACK_UI); i < static_cast<int>(OBJECT_TYPE::END); ++i)
		{
			for (auto iter : m_objectVector[i])
			{
				iter->LateUpdate(_deltaTime);
			}
		}
	}
	else
	{
		for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
		{
			for (auto iter : m_objectVector[i])
			{
				iter->LateUpdate(_deltaTime);
			}
		}
	}
}

void Scene::AddObject(GameObject* _object)
{
	queue<GameObject*> q;
	q.push(_object);

	const CollisionManager* collisionMgr = m_managerSet->GetCollisionManager();


	while (!q.empty())
	{
		GameObject* tmp = q.front();
		OBJECT_TYPE type = tmp->GetObjectType();

		m_objectVector[static_cast<int>(type)].push_back(tmp);
		
		/// 충돌체를 가지는 경우에는 충돌매니저의 트리에 충돌체를 추가한다.
		BoxCollider* box = tmp->GetComponent<BoxCollider>();
		CircleCollider* circle = tmp->GetComponent<CircleCollider>();
		if (box != nullptr)
		{
			collisionMgr->AddColider(box);
		}
		if (circle != nullptr)
		{
			collisionMgr->AddColider(circle);
		}

		for (auto child : tmp->GetChildren())
		{
			q.push(child);
		}

		q.pop();
	}
}

void Scene::DestoryGroupObject(OBJECT_TYPE _type)
{ 
	for (auto iter : m_objectVector[static_cast<int>(_type)])
	{
		iter->Finalize();
		delete iter;
	}
	
	// 배열 초기화
	m_objectVector[static_cast<int>(_type)].clear();
}
