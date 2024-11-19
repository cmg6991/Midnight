#include "UserScriptsPCH.h"
#include "FireFly.h"

FireFly::FireFly()
	:MonoBehaviour(typeid(this).name()),
	m_start(Vector2::Zero), m_end(Vector2::Zero), m_distance(Vector2::Zero),m_isPositive(true), m_speed(0.f)
	,m_target(nullptr), m_time(0.f), m_rotation(0.f)
{

}

FireFly::~FireFly()
{

}

Component* FireFly::Clone()
{
	FireFly* clone = new FireFly();

	return clone;
}

void FireFly::Start()
{
	Transform* transform = GetComponent<Transform>();
	Vector2 current = transform->GetPosition();
	m_start = current - m_distance;
	m_end = current + m_distance;
	m_direction = (m_end - m_start).GetNormalize();
}

void FireFly::Update(float _deltaTime)
{
	if (m_state == FIREFLY_STATE::CURVE)
	{
		Transform* transform = GetComponent<Transform>();

		Vector2 distance = m_direction * m_speed * _deltaTime;
		transform->AddPosition(distance);

		Vector2 current = transform->GetPosition();

		float xoffset = fabs(distance.x);
		float yoffset = fabs(distance.y);
		float ypoint1 = m_start.y + 300.f;
		float ypoint2 = m_start.y + 50.f;
		if (m_isPositive)
		{
			if (current.y > ypoint1)
			{
				m_direction.y *= -1.f;
				current.y -= yoffset * 100.f;
			}
			if (current.y < ypoint2)
			{
				m_direction.y *= -1.f;
				current.y += yoffset * 100.f;
			}
			if (current.x > 1000.f)
			{
				m_direction *= -1.f;
				current.x -= xoffset * 100.f;
			}
			if (current.x < -1000.f)
			{
				m_direction.x *= -1.f;
				current.x += xoffset * 100.f;
			}
			transform->SetPosition(current);
		}
	}
	if (m_state == FIREFLY_STATE::ETC)
	{
		m_time += _deltaTime;


		if (m_time > 2.f)
		{
			Transform* fireflyTransform = GetComponent<Transform>();
			fireflyTransform->SetPosition(m_start);
			m_state = FIREFLY_STATE::CURVE;
			m_time = 0.f;

			GetComponent<PointLightRenderer>()->SetIntensity(2.f);
			  
			GetComponent<PointLightRenderer>()->SetMinimumIntensity(1.f);
			GetComponent<PointLightRenderer>()->SetIntensityChangeSpeed(0.2f);
			GetComponent<PointLightRenderer>()->SetFixedIntensity(false);
			GetComponent<PointLightRenderer>()->SetRGB(Vector3F(1.f, 1.f, 0.1f));
		}


	}
	if(m_state == FIREFLY_STATE::CIRCLE)
	{
		m_time += _deltaTime;
		if (m_time <= 5.f)
		{
			Transform* fireflyTransform = GetComponent<Transform>();
			Vector2 fireflyPosition = fireflyTransform->GetPosition();

			Transform* playerTransform = m_target->GetComponent<Transform>();
			Vector2 playerPosition = playerTransform->GetPosition();

			float radius = 120.0f;
			float angleSpeed = 100.f;

			//radian 값으로 변경
			float angleRadian = m_rotation * (3.14159f / 180.0f);

			float x = radius * cos(angleRadian);
			float y = radius * sin(angleRadian);

			Vector2 position = playerPosition + Vector2(x, y);
			fireflyTransform->SetPosition(position);

			m_rotation += angleSpeed * _deltaTime;
			if (m_rotation >= 360.0f)
				m_rotation -= 360.0f;
		}
		else
		{
			m_state = FIREFLY_STATE::ETC;
			m_time = 0;
			GetComponent<PointLightRenderer>()->SetIntensity(0.f);
			GetComponent<PointLightRenderer>()->SetFixedIntensity(true);

		}
	}
}

void FireFly::SetUp(Vector2 _distance, float _speed)
{
	m_distance = _distance;
	m_speed = _speed;
}

void FireFly::OnTriggerEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetName() == "player")
	{
		m_target = _collision.otherObject;
		m_state = FIREFLY_STATE::CIRCLE;
	}
}

void FireFly::DebugRender(D2DRenderer* _d2DRenderer)
{
	if (m_state == FIREFLY_STATE::CIRCLE)
	{
		Vector2 pos = GetComponent<Transform>()->GetPosition();
		_d2DRenderer->DrawFillRectangle2(pos - Vector2(30, 30), pos + Vector2(30, 30), D2D1::ColorF::Red);
	}
}
