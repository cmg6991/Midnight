#pragma once


enum class EFFECT_TYPE
{
	GAUSSIAN_BLUR,
	CHROMAKEY,
	POINT_DIFFUSE,

	END,
};


enum class EXTRACT_COLOR
{
	RED,
	BLUE,
	GREEN,
};


enum class RENDER_TARGET
{
	DEFALUT,
	LIGHT,
};

enum class FONT_TYPE
{
	DEFALUT,
	SPEECH_BUBBLE,
	TALK,


	END,
};


// 이미지 반전 타입
enum class FLIP_TYPE
{
	NONE,
	X_FLIP,
	Y_FLIP,
	XY_FLIP,
};