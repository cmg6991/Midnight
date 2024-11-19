#pragma once


class Collider;

struct AABB
{
	Vector2 minPoint;
	Vector2 maxPoint;

	AABB();
	AABB(const Vector2& _minPoint, const Vector2& _maxPoint);

	// 2개의 AABB를 병합
	AABB Union(const AABB& _other)const;
	// 사각형의 넓이 반환  
	float GetArea()const;
	// 콜라이더가 확장한 사각형 내부에 있는지 
	bool Contains(Collider* _collider) const;

	bool IsCollision(const AABB& _other) const;
};

