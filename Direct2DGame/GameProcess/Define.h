#pragma once

class GameObject;
class Collider;

/// ===================== 오브젝트 ==============================

/// <summary>
/// 오브젝트의 타입의 번호가 작을수록 모든 이벤트에서
/// 우선순위를 가진다, 다른의미로 큰 번호일 수록 가장 상단에
/// 랜더링한다.
/// </summary>
enum class OBJECT_TYPE
{
	BACKGROUND, // 배경화면

	BACKGROUND_LIGHT, // 배경 라이트 

	TILE, // 타일 
	INTERACTIVE_ITEM, // 상호작용 아이템 
	CHASER_BLOCKER, // 집사 떨어지기 방지용
	RABBIT_TUNNEL, //
	BACK_PARTICLE, //플레이어 뒤에 그려질 파티클
	CHASER, // 집사
	MIDDLE_LIGHT, // 중간 라이트
	PLAYER, // 플레이어

	FOG, // 안개 
	PARTICLE, // 파티클
	FINAL_LIGHT, // 마지막 라이트

	/* 캐릭터 위에 출력될 장식 오브젝트
	* TODO : 이 오브젝트 타입을 가진 오브젝트는 캐릭터가 지나가면 반투명해져야 한다. 
	*/
	FRONT_DECO, 

	/// 아래의 오브젝트 타입부터는 마우스 이벤트가 발생함
	BACK_UI,	/// 항상 FRONT UI보다 뒤에 그려진다
	FRONT_UI,
	MOUSE,
	END = 32,
};


enum class OBJECT_STATE	
{
	ALIVE,
	TO_BE_DESTORYED,
	DESTORY,
};

/// <summary>
/// 컴포넌트의 호출 순서를 명시함
/// 낮은 숫자일수록 자료구조 맵에서 앞쪽에 정렬되어
/// 게임오브젝트의 업데이트에서 항상 앞쪽 먼저 업데이트를 호출한다.
/// </summary>
enum class CALL_ORDER
{
	CAMERA_AFFECTED_LAYER,
	RIGID_BODY,
	MONO_BEHAVIOUR,
	RENDERER,
	ANIMATOR,
	TEXT,
	TRANSFORMM,
	COLLIDER,
	BOX2D_COLLIDER,
	PARTICLE_SYSTEM,
	LIGHT,
	UI
};

/// ============================= 랜더링 관련 ====================================
enum class RENDERING_MODE
{
	PRE_RENDER,
	RENDER, 
	POST_RENDER,
};


/// =================================== 컴포넌트 관련 ==============================
enum class COLLIDER_TYPE
{
	CIRCLE,
	BOX,
};

// 가장 기본적인 트랜스폼 컴포넌트의 정보를 저장한다.
struct TransformInfo
{
	TransformInfo() = default;
	TransformInfo(Vector2 _position, Vector2 _scale, float _rotation = 0.f)
		:position(_position), scale(_scale), rotation(_rotation)
	{}

	Vector2 position = Vector2::Zero;
	Vector2 scale = Vector2::One;
	float rotation = 0.f;
};

struct BoxColliderInfo
{
	BoxColliderInfo(Vector2 _offset = Vector2::Zero, Vector2 _scale =Vector2::Zero
		, bool _rotatable = false, bool _isTrigger = false)
		: offsetPosition(_offset),scale(_scale),rotatable(_rotatable)
		, isTrigger(_isTrigger)
	{}

	Vector2 offsetPosition;
	Vector2 scale;
	bool isTrigger; 
	bool rotatable;
};

struct CircleInfo
{
	CircleInfo(Vector2 _offset, float _radius, bool _isTrigger = false)
		:radius(_radius), positionOffset(_offset)
		,isTrigger(_isTrigger)
	{}

	bool isTrigger;
	Vector2 positionOffset = Vector2::Zero;
	float radius = 0.f;
};

// BarUI를 만드는데 필요한 정보들
struct BarUIInfo
{
	Vector2 positionOffset; // object와 떨어진 거리
	Vector2 innerBarOffset; // 내부바와 가장자리 바의 오프셋
	Vector2 barScale; // 바의 크기 
	float barLength; // 현재 바의 길이 0.f~ 1.f
	
	D2D1::ColorF innerFillBarColor = D2D1::ColorF(ColorF::Black);  // 내부를 채우는 바의 색
	D2D1::ColorF innerEmptyBarColor = D2D1::ColorF(ColorF::Red); // 내부빈공간 바의 색
	D2D1::ColorF edgeColor = D2D1::ColorF(ColorF::White);// 외부 바의 색
};

/// =================== 카메라 관련 =========================

enum class CAMERA_EFFECT_TYPE
{
	FADE_IN,
	FADE_OUT,
	LETTERBOX,
	END,
};


// 연출 타입 
enum class ACTION_TYPE
{
	OBJECT_MOVE, // 오브젝트 이동 연출
	OBJECT_TALK, // 오브젝트 대사 연출 
	CAMERA_MOVE, // 카메라 이동 연출
	CAMERA_EFFECT_ON, // 카메라 이펙트 연출
	LETTERBOX_OFF,
	WAIT_TRIGGER, // 트리거 대기 상태
	OFF_INPUT, // 키입력을 비활성화한다.
	ON_INTPUT, // 키입력을 활성화한다.
};

// Actor의 대사 정보
struct TalkingInfomation
{
	wstring text; // 대사
	ColorF textColor = ColorF::Black; // 대사 색깔
	wstring imageKey; // 말풍선이미지 키값
	float outputTempo = 0.1f; // 출력 탬포
};

struct MovingInfomation
{
	Vector2 distance; // 이동거리
	float moveSpeed; // 이동 속도
	wstring playAnimationName; // 재생할 애니메이션 이름 
	
}; 


struct ActionInfomation
{
	ACTION_TYPE type; // 연출 타입
	int actingOrder; // 대사 순서

	string actorName; // 오브젝트 이름 
	TalkingInfomation talkingInfo; // 대사 정보
	MovingInfomation movingInfo; // 이동 정보
	CAMERA_EFFECT_TYPE cameraEffectType =CAMERA_EFFECT_TYPE::END; // 카메라 효과

	bool isStraightAction = false; // 연속되는 연출인지
};
 

/// ========================= 충돌 관련 =========================================

// BOX 와 BOX 가 충돌했을때 방향
enum class COLLISION_DIRECT
{
	NONE, // 리지드 바디이기에서 계산한다.
	UP, // 자신 기준으로 상단
	DOWN, //  자신 기준으로 하단
	LEFT, // 자신 기준으로 왼쪽
	RIGHT, // 자신 기준으로 오른쪽
};


// 충돌정보 
struct Collision
{
	GameObject* otherObject;
	Collider* otherCollider;
	Collider* myCollider;

	mutable COLLISION_DIRECT direct;
};

// struct Box2DCollision
// {
// 	GameObject* otherObject;
// 	
// 
// };




///  ================================== 키입력관련 =================================
enum class KEY_STATE
{
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
	NONE, // 눌리지 않았고, 이전에도 눌리지 않은 상태
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,

	Q, W, E, R, T, Y, U, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC, TAB,

	LMOUSE, RMOUSE,
	F1, F2, F3, F4, F5,

	LAST, //enum의 끝
};


