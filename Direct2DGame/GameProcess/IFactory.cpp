#include "GameProcessPCH.h"
#include "IFactory.h"
#include "GameObject.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "RigidBody.h"
#include "TextureRenderer.h"
#include "MouseEvent.h"

IFactory::~IFactory()
{

}

GameObject* IFactory::CreateGameObject(const string& _name, const ManagerSet* _managerSet, OBJECT_TYPE _type, const TransformInfo& _info)
{

	GameObject* object = new GameObject(_name, _managerSet, _type);

	Transform* transform = object->CreateComponent<Transform>();
	transform->SetPosition(_info.position);
	transform->SetScale(_info.scale);
	transform->SetRotation(_info.rotation);
	return object;
}


void IFactory::CreateBoxCollider(GameObject* _object, BoxColliderInfo _info)
{
	BoxCollider* box = _object->CreateComponent<BoxCollider>();

	// BoxCollider 스케일값이 Zero인 경우 Transform의 Scale을 따라간다.
	if (_info.scale == Vector2::Zero)
	{
		Vector2 scale = _object->GetComponent<Transform>()->GetScale();
		box->SetScale(scale);
	}
	else
	{
		box->SetScale(_info.scale);
	}
	box->SetOffset(_info.offsetPosition);
	box->SetRotatble(_info.rotatable);
	box->SetTrigger(_info.isTrigger);

}

void IFactory::CreateCircleColldier(GameObject* _object, CircleInfo _intfo)
{
	CircleCollider* circle = _object->CreateComponent<CircleCollider>();

	circle->SetRadius(_intfo.radius);
	circle->SetOffset(_intfo.positionOffset);
	circle->SetTrigger(_intfo.isTrigger);
}

void IFactory::CreateRigidBody(GameObject* _object, float _mass /*= 1.f*/)
{
    RigidBody* rigid =_object->CreateComponent<RigidBody>();
	rigid->SetMass(_mass);
}


void IFactory::CreateTextureRenderer(GameObject* _object
	, const wstring& _key, Vector2 _offset /*= Vector2::Zero*/)
{
	TextureRenderer* renderer = _object->CreateComponent<TextureRenderer>();

	renderer->SetKey(_key);
	renderer->SetOffset(_offset);
}

void IFactory::CreateUI(GameObject* _object)
{
	_object->CreateComponent<MouseEvent>();
}

