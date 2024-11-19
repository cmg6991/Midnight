#pragma once


/// <summary>
/// 팩토리에서 생성 가능한 오브젝트 리스트 
/// </summary>
enum class FACTORY_OBJECT 
{
	PLAYER, // 플레이어
	RABBIT, // 토끼
	CHASER, // 집사
	KEY, // 상호작용 가능한 키 
	DOOR, // 상호장용 가능한 문
	GROUND, // 땅 
	CEILING, //천장 
};

enum class ITEM_TYPE
{
	NONE, // 초기화 X
	KEY, // 문여는 용도의 아이템 
	DOOR, // 문 : 열기위해서는 키가 필요함

};

