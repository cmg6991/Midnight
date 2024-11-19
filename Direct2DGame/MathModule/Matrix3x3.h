#pragma once


// 아핀공간 행렬변환을 위한 3x3
// 
// direct2d에서는 행기준 방식을 사용한다
// x1 y1 z1               x1 x2 x3
// x2 y2 z2               y1 y2 y3
// x3 y3 z3 -> 열기준행렬  z1 z2 z3 -> 행기준행렬
struct Matrix3x3
{
	inline constexpr Matrix3x3() = default;
	inline explicit constexpr Matrix3x3(const Vector3& _col0, const Vector3& _col1, const Vector3& _col2) 
	{ Cols = { _col0,_col1,_col2 }; }

	inline const Vector3& operator[](int InIndex) const;
	inline Vector3& operator[](int InIndex);

	inline Matrix3x3 operator*(float InScalar) const;
	inline Matrix3x3 operator*(const Matrix3x3& InMatrix) const;
	inline Vector3 operator*(const Vector3& InVector) const;


	inline Matrix3x3 Transpose() const;

	// 항등행렬
	static const Matrix3x3 Identity;

	// 멤버 변수
	std::array<Vector3, 3> Cols = { Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ };
};

inline const Vector3& Matrix3x3::operator[](int InIndex) const
{
	assert(InIndex < 3);
	return Cols[InIndex];
}

inline Vector3& Matrix3x3::operator[](int InIndex)
{
	assert(InIndex < 3);
	return Cols[InIndex];
}


inline Matrix3x3 Matrix3x3::operator*(float InScalar) const
{
	return Matrix3x3(
		Cols[0] * InScalar,
		Cols[1] * InScalar,
		Cols[2] * InScalar
 	);
}
inline Matrix3x3 Matrix3x3::operator* (const Matrix3x3& InMatrix) const
{
	Matrix3x3 transposedMatrix = Transpose();
	return Matrix3x3(
		Vector3(transposedMatrix[0].Dot(InMatrix[0]), transposedMatrix[1].Dot(InMatrix[0]), transposedMatrix[2].Dot(InMatrix[0])),
		Vector3(transposedMatrix[0].Dot(InMatrix[1]), transposedMatrix[1].Dot(InMatrix[1]), transposedMatrix[2].Dot(InMatrix[1])),
		Vector3(transposedMatrix[0].Dot(InMatrix[2]), transposedMatrix[1].Dot(InMatrix[2]), transposedMatrix[2].Dot(InMatrix[2]))
	);
}

inline Vector3 Matrix3x3::operator* (const Vector3& InVector) const
{
	Matrix3x3 transposedMatrix = Transpose();
	return Vector3(
		transposedMatrix[0].Dot(InVector),
		transposedMatrix[1].Dot(InVector),
		transposedMatrix[2].Dot(InVector)
	);
}

// 전치 행렬
inline Matrix3x3 Matrix3x3::Transpose() const
{
	return Matrix3x3(
		Vector3(Cols[0].x, Cols[1].x, Cols[2].x),
		Vector3(Cols[0].y, Cols[1].y, Cols[2].y),
		Vector3(Cols[0].z, Cols[1].z, Cols[2].z)
	);
}

