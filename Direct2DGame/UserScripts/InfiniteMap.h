#pragma once
#include <MonoBehaviour.h>

enum class OBJ_NAME
{
	PILLAR,
	FOG,
	BACKGROUND,
	ENDING_BACKGROUND
};

class Factory;
class InfiniteMap : public MonoBehaviour
{
public: 
	InfiniteMap();
	~InfiniteMap();
	Component* Clone() override { return nullptr; }

public:
	void SetUp(OBJ_NAME _type, Vector2 _initPos);
	void Update(float _deltaTime) override;
	//void DebugRender(D2DRenderer* _d2DRenderer) override;

private:
	void Create();
	void Destroy();

private:
	Vector2 m_initPos;
	OBJ_NAME m_objType;
	float m_step;
	float m_halfxSize;
	Transform* m_lastObjTransform;
	D2DCamera* m_camera;
	Factory* m_factory;
	vector<GameObject*> m_objs;
	Scene* m_scene;

	float m_destroyPos;
	float m_createPos;

	const float m_halfScreenWidth = 960.f;
	float m_rightBoundary;
	float m_leftBoundary;
};

