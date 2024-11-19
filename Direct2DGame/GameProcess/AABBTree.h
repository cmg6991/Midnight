#pragma once

#include "Broadphase.h"
#include "AABB.h"
#include "Collider.h"
struct Node;
class CollisionManager;

/// <summary>
/// 충돌 체크 알고리즘 AABBTree
/// 각각의 콜라이더를 AABB사각형으로 확장하고
/// 확장한 사각형을 m_margin만큼 확장한후에 
/// 면적에따라서 Tree를 구성하고 정렬한다
/// 
/// </summary>
class AABBTree :
    public Broadphase
{
public:
    AABBTree(float _margin, CollisionManager* _collisionManager);
    ~AABBTree();

    void Add(Collider* _collider) override;
    void Remove(Collider* _collider) override;
    void Update() override;
    ColliderPairList& ComputePairs() override;
    
    // 점과 충돌하는 충돌체들 반환
    void Pick(const Vector2& _point, ColliderVector& _colliderVector) override;

    // 사각형 내부에 충돌하는  Collider 반환
    void Query(const AABB& _aabb, ColliderVector& _output) const override;
    
	RayCastResult RayCast(const Vector2& _direct
        , const Vector2& _center, float _maxDistance = 0.f) const override;


    // 트리를 초기화한다.
    void Clear();

    void DebugRender(D2DRenderer* _d2DRenderer);
private:
    typedef std::vector<Node*> NodeVector;
    void UpdateNodeHelper(Node* _node);
    void InsertNode(Node* _node, Node** _parent);
    void RemoveNode(Node* _node);
    void ComputePairsHelper(Node* _n0, Node* _n1);
    void ClearChildrenCrossFlagHelper(Node* _node);
    void CrossChildren(Node* _node);

private:
    Node* m_root; 
    ColliderPairList m_pairs;
    const float m_margin;

    CollisionManager* m_collisionManager; 
    NodeVector m_invalidNodes;
    NodeVector m_removeNodes;
};

struct Node
{
    Node() :parent(nullptr)
        , collider(nullptr)
        , children{ nullptr,nullptr } 
        , childrebCrossed(false)
        , aabb()
    {}
    
    bool IsLeaf()const
    {
        return children[0] == nullptr;
    }

    // 자식노드에 추가
    void SetBranch(Node* _n0, Node* _n1)
    {
        _n0->parent = this;
        _n1->parent = this;

        children[0] = _n0;
        children[1] = _n1;
    }

    // Leaf노드로 만든다
    void SetLeaf(Collider* _collider)
    {
        this->collider = _collider;
 
        children[0] = nullptr;
        children[1] = nullptr;
    }

    void UpdateAABB(float _margin)
    {
        if (IsLeaf())
        {
            // make fat AABB
            // 확장한 AABB생성
            const Vector2 marginVec(_margin, _margin);
            aabb.minPoint = collider->GetMinPoint() - marginVec;
            aabb.maxPoint = collider->GetMaxPoint() + marginVec;
        }
        else
        {
            // make union of child AABBs of child nodes;
            // 자식노드를 조합해서 AABB만들기
            aabb = children[0]->aabb.Union(children[1]->aabb);
        }
    }

    // 형제 반환
    Node* GetSibling() const
    {
        assert(parent);
        return this == parent->children[0] ? parent->children[1] : parent->children[0];
    }


    Node* parent;
    Node* children[2];

    bool childrebCrossed;
    AABB aabb;
    Collider* collider;
}; 