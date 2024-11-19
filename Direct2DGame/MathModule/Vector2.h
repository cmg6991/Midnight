#pragma once

struct Vector2
{
public:
	float x;
	float y;
	
	inline constexpr Vector2():x(0.f),y(0.f){}
	inline explicit constexpr Vector2(int _x, int _y);
	inline explicit constexpr Vector2(float _x, float _y);

	/// 연산자
	inline constexpr Vector2 operator-() const;
	inline constexpr Vector2 operator*(float _scalar) const;
	inline constexpr Vector2 operator/(float _scalar) const;
	inline constexpr Vector2 operator*(const Vector2& _other) const;
	inline constexpr Vector2 operator+(const Vector2& _other) const;
	inline constexpr Vector2 operator-(const Vector2& _other) const;
	inline constexpr Vector2& operator*=(float _scale);
	inline constexpr Vector2& operator/=(float _scale);
	inline constexpr Vector2& operator+=(const Vector2& _other);
	inline constexpr Vector2& operator-=(const Vector2& _other);
	inline constexpr bool operator==(const Vector2& _other);
	inline constexpr bool operator!=(const Vector2& _other);


	// 루트 제곱근 (길이)
	inline float Length() const;

	// 제곱근 반환
	inline constexpr float LengthSquared() const;

	// 벡터 정규화
	void Normalize();

	// [[nodiscard]] : 반환값을 쓰지 않으면 경고
	[[nodiscard]] Vector2 GetNormalize() const;

	// 반환값은 라디안입니다!!
	inline float Angle() const;

	// 직교 좌표계 -> 극좌표계 변환
	inline Vector2 ToPolarCoordinate() const;

	// 극좌표계 -> 직교좌표계 변환
	inline Vector2 ToCartesianCoordinate() const;

	inline Vector2 ChangeYSign ( );

	// 내적연산
	inline constexpr float Dot(const Vector2& _other) const;
	// 외적 연산
	inline constexpr float Cross ( const Vector2& _other ) const;
	
	std::string ToString() const;
	
	inline D2D1_POINT_2F ToPoint2F();

	// 기준점을 기준으로 point를 radian만큼 회전한 벡터를 반환
	static Vector2 RotateRadian(const Vector2& _point, const Vector2& _center, float _radian);

	// 선분과 점사이의 최단경로를 반환
	static float PointToLineSegment ( const Vector2& point , const Vector2& line1 ,const  Vector2& line2 );

	// 두 점사이에 있는 특정 비율의 지점 반환
	static Vector2 Lerp ( const Vector2& v1 , const Vector2& v2 , float ratio );

	// 두 점의 거리
	static float Distance ( const Vector2& v1 , const Vector2& v2 );

	// 정적멤버변수
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 One;
	static const Vector2 Zero;
};


inline Vector2 Vector2::ChangeYSign ( )
{
	return Vector2 ( x , -y );
}

inline D2D1_POINT_2F Vector2::ToPoint2F()
{
	D2D1_POINT_2F point{};
	point.x = x;
	point.y = y;
	return point;
}

inline Vector2 Vector2::RotateRadian(const Vector2& _point, const Vector2& _center, float _radian)
{
	float cosTheta = std::cos(_radian);
	float sinTheta = std::sin(_radian);

	Vector2 relative = _point - _center;
	Vector2 rotated{};
	rotated.x = _center.x + relative.x * cosTheta - relative.y * sinTheta;
	rotated.y = _center.y + relative.x * sinTheta + relative.y * cosTheta;

	return rotated;
}


inline constexpr Vector2::Vector2(int _x, int _y)
	:x((float)_x)
	, y((float)_y)
{}

inline constexpr Vector2::Vector2(float _x, float _y)
	: x(_x)
	, y(_y)
{}

inline constexpr Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

inline constexpr Vector2 Vector2::operator*(float _scalar) const
{
	return Vector2(x * _scalar, y * _scalar);
}

inline constexpr Vector2 Vector2::operator/(float _scalar) const
{
	return Vector2(x / _scalar, y / _scalar);
}

inline constexpr Vector2 Vector2::operator*(const Vector2& _other) const
{
	return Vector2(x * _other.x, y * _other.y);
}

inline constexpr Vector2 Vector2::operator+(const Vector2& _other) const
{
	return Vector2(x + _other.x, y + _other.y);
}

inline constexpr Vector2 Vector2::operator-(const Vector2& _other) const
{

	return Vector2(x - _other.x, y - _other.y);
}

inline constexpr Vector2& Vector2::operator*=(float _scale)
{
	x *= _scale;
	y *= _scale;

	return *this;
}

inline constexpr Vector2& Vector2::operator/=(float _scale)
{
	x /= _scale;
	y /= _scale;

	return *this;
}

inline constexpr Vector2& Vector2::operator+=(const Vector2& _other)
{
	x += _other.x;
	y += _other.y;

	return *this;
}

inline constexpr Vector2& Vector2::operator-=(const Vector2& _other)
{
	x -= _other.x;
	y -= _other.y;

	return *this;
}

inline constexpr bool Vector2::operator==(const Vector2& _other)
{
	return (x == _other.x && y == _other.y);
}

inline constexpr bool Vector2::operator!=(const Vector2& _other)
{
	return (x != _other.x || y != _other.y);
}

inline float Vector2::Length() const
{
	return sqrtf(LengthSquared());
}

inline constexpr float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

inline float Vector2::Angle() const
{
	return atan2f(y, x);
}


inline Vector2 Vector2::ToPolarCoordinate() const
{
	return Vector2(Length(), Angle());
}

inline Vector2 Vector2::ToCartesianCoordinate() const
{
	// 극좌표계에서는 x는 반지름 y는 각(rad)으로 활용
	float sinValue = sinf(y);
	float cosValue = cosf(y);

	return Vector2(x * sinValue, x * cosValue);
}

inline constexpr float Vector2::Dot(const Vector2& _other) const
{
	return x* _other.x + y * _other.y;
}

inline constexpr float Vector2::Cross ( const Vector2& _other )const
{
	return x * _other.y - y * _other.x;
}
