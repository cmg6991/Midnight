#include "GameProcessPCH.h"
#include "BoxRenderer.h"
#include "Transform.h"
#include "GameObject.h"

BoxRenderer::BoxRenderer()
	:MonoBehaviour(typeid(this).name())
{

}

BoxRenderer::~BoxRenderer()
{

}

Component* BoxRenderer::Clone()
{
	BoxRenderer* clone = new BoxRenderer();

	return clone;
}

void BoxRenderer::Render(D2DRenderer* _d2DRenderer)
{
	Transform* transform = GetComponent<Transform>();

	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();

	Vector2 leftTop{ position.x - scale.x * 0.5f , position.y + scale.y * 0.5f };
	Vector2 rightBottom{ position.x + scale.x * 0.5f, position.y - scale.y * 0.5f };

	float radian = transform->GetRotation();
	_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::LightBlue, radian);
}
