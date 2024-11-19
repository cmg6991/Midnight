#pragma once

///파티클 시스템 네임스페이스
namespace ps
{
	// 랜덤 사용 방식
	enum class RANDOM_TYPE
	{
		NONE,		// 랜덤 사용 X
		LINEAR,		// 선형
		NORMAL,		// 정규분포
		DISCRETE	// 이산다항분포
	};


	// 변화량 적용 방식 (값 or 비율)
	enum class VARIANCE_TYPE
	{
		VALUE,				// 값
		PERCENT,			// 비율
		//LIFETIME,			// 시간에 비례 (min -> max)
		//INVERSE_LIFETIME	// 시간에 반비례 (max - > min)
		//,USER_DEFINE //사용자 정의 함수
	};


	// 방출 모형
	enum class EMISSION_SHAPE
	{
		SQUARE, // halfWidth, halfHeight
		CIRCLE,	// radius
		CONE,	// minAngle, maxAngle, radius
	};


	enum class END_ACTION
	 {
	 	SLEEP,
	 	DESTROY,
	 	//CALLBACK
	 };

	enum class TRIGGER
	{
		NONE,
		BIRTH,
		DEATH,
		COLLISION,
		TIME
	};


	// 파티클 값
	struct ParticleValue
	{
		float mininum;				// 최소값
		float maximum;				// 최대값
		RANDOM_TYPE randomType;		// 랜덤 방식

	public:
		ParticleValue()
			:mininum(1), maximum(1), randomType(RANDOM_TYPE::NONE)
		{
		}

		ParticleValue(float _min)
			: mininum(_min), maximum(_min), randomType(RANDOM_TYPE::NONE)
		{
		}

		ParticleValue(float _min, float _max, RANDOM_TYPE _type)
			: mininum(_min), maximum(_max), randomType(_type)
		{
		}
	};

	// 파티클 변화량 값
	struct VarianceValue
	{
		float mininum;				// 최소값
		float maximum;				// 최대값
		RANDOM_TYPE randomType;		// 랜덤 방식
		VARIANCE_TYPE varianceType; // 변량 방식

	public:
		VarianceValue()
			:mininum(0), maximum(0), randomType(RANDOM_TYPE::NONE), varianceType(VARIANCE_TYPE::VALUE)
		{
		}

		VarianceValue(float _min)
			: mininum(_min), maximum(_min), randomType(RANDOM_TYPE::NONE), varianceType(VARIANCE_TYPE::VALUE)
		{
		}

		VarianceValue(float _min, float _max, RANDOM_TYPE _randomType, VARIANCE_TYPE _varType)
			:mininum(_min), maximum(_max), randomType(_randomType), varianceType(_varType)
		{
		}
	};


}