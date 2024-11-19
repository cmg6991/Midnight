
#include"GameProcessPCH.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "AABBTree.h"
#include "Scene.h"

CollisionManager::CollisionManager()
	:m_inputManager(nullptr)
	,m_sceneManager(nullptr)
	,m_collisionCheck{}
	,m_aabbTree(nullptr)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Initalize(InputManager* _inputManager, SceneManager* _sceneManager)
{
	m_inputManager = _inputManager;
	m_sceneManager = _sceneManager;

	// AABBTree 생성 
	m_aabbTree = new AABBTree(25.f,this);
}

void CollisionManager::Finalize()
{

	// 메모리 해제
	delete m_aabbTree;
}

void CollisionManager::DebugRender(D2DRenderer* _d2DRenderer)
{
	m_aabbTree->DebugRender(_d2DRenderer);
}

void CollisionManager::Update()
{
	// 새로추가된 콜라이더를 AABBTree에 추가는 오브젝트가 담당한다 

	// AABBTree 삭제예정인 오브젝트, 확장한 사각형을 벗어난경우 처리
	m_aabbTree->Update();

	// 충돌한 콜라이더 pairList를 받아온다 
	ColliderPairList& pairList = m_aabbTree->ComputePairs();

	//받아온 Pair정보를 맵으로 정보를 갱신 
	for (auto& colldierPair : pairList)
	{
		ColliderKey key(colldierPair.first, colldierPair.second);

		auto iter = m_collisionInfomations.find(key);

		// 새로운 정보 삽입
		if (iter == m_collisionInfomations.end())
		{
			// 이전프레임 전프레임 충돌하지 않음 설정
			CollisionInfomation info = { colldierPair.first
				,colldierPair.second
				,false,true };
			m_collisionInfomations.insert(std::make_pair(key, std::move(info)));
		}
		else
		{
			// 이번 프레임 충돌
			iter->second.currentCollision = true;
		}
	}

	// 오브젝트에게 충돌 이벤트 호출
	for (auto& iter : m_collisionInfomations)
	{
		Collider* collider1 = iter.second.collider1;
		Collider* collider2 = iter.second.collider2;

		GameObject* object1 = collider1->GetGameObject();
		GameObject* object2 = collider2->GetGameObject();

		Collision collision1{};
		collision1.otherCollider = collider2;
		collision1.otherObject = object2;
		collision1.myCollider = collider1;

		Collision collision2{};
		collision2.otherCollider = collider1;
		collision2.otherObject = object1;
		collision2.myCollider = collider2;

		if (iter.second.currentCollision) // 이번프레임 충돌중
		{
			if (iter.second.prevCollision) // 이전프레임 충돌
			{
				// Stay
				if (collider1->IsTrigger() || collider2->IsTrigger())
				{
					object1->OnTriggerStay(collision1);
					object2->OnTriggerStay(collision2);
				}
				else
				{
					object1->OnCollisionStay(collision1);
					object2->OnCollisionStay(collision2);
				}
			}
			else // 이전프레임에는 충돌하지않음
			{
				// Enter
				if (collider1->IsTrigger() || collider2->IsTrigger())
				{
					object1->OnTriggerEnter(collision1);
					object2->OnTriggerEnter(collision2);
				}
				else
				{
					object1->OnCollisionEnter(collision1);
					object2->OnCollisionEnter(collision2);
				}
			}
		}
		else // 이번 프레임 충돌하지 않음
		{
			if (iter.second.prevCollision) // 이전 프레임에는 충돌함
			{
				// Exit
				if (collider1->IsTrigger() || collider2->IsTrigger())
				{
					object1->OnTriggerExit(collision1);
					object2->OnTriggerExit(collision2);
				}
				else
				{
					object1->OnCollisionExit(collision1);
					object2->OnCollisionExit(collision2);
				}
			}
		}

		// 이번 프레임의 정보를 저장한다.
		iter.second.prevCollision = iter.second.currentCollision;
		iter.second.currentCollision = false;
	}
}

void CollisionManager::CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const
{
	// 비트 연산자를 통해서 그룹간의 충돌정보를 관리한다.
	m_collisionCheck[static_cast<int>(_left)] |= (1 << static_cast<int>(_right));
	m_collisionCheck[static_cast<int>(_right)] |= (1 << static_cast<int>(_left));
}

void CollisionManager::OffCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const
{
	int info = m_collisionCheck[static_cast<int>(_left)];

	// 비트 연산자를 통해서 그룹간의 충돌정보를 관리한다.
	m_collisionCheck[static_cast<int>(_left)] |= (0 << static_cast<int>(_right));
	m_collisionCheck[static_cast<int>(_right)] |= (0 << static_cast<int>(_left));
}

void CollisionManager::AddColider(Collider* _collider) const
{
	m_aabbTree->Add(_collider);
}

void CollisionManager::Clear()
{
	m_collisionInfomations.clear();
	m_aabbTree->Clear();
}

void CollisionManager::DetectPointToCollider(const Vector2& _point, vector<Collider*>& _colliderVector) const
{
	m_aabbTree->Pick(_point, _colliderVector);
}

void CollisionManager::DetectBoxToCollider(const Vector2& _minPoint, const Vector2& _maxPoint, vector<Collider*>& _colliderVector) const
{
	AABB aabb{};
	aabb.minPoint.x = _minPoint.x;
	aabb.minPoint.y = _minPoint.y;
	aabb.maxPoint.x = _maxPoint.x;
	aabb.maxPoint.y = _maxPoint.y;

	m_aabbTree->Query(aabb, _colliderVector);

}

bool CollisionManager::IsCollisionType(Collider* _left, Collider* _right)
{
	OBJECT_TYPE left = _left->GetGameObject()->GetObjectType();
	OBJECT_TYPE right = _right->GetGameObject()->GetObjectType();

	int leftIndex = static_cast<int>(left);
	int rightIndex = static_cast<int>(right);

	if (m_collisionCheck[leftIndex] & (1 << rightIndex))
		return true;

	return false;
}
