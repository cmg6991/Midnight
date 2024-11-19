#pragma once

class D2DRenderer;

/// <summary>
/// 이펙트를 담당하는 클래스 
/// 
/// 반환해주는 비트맵은 사용자가 직접 Release해야한다
/// ComPtr은 사용할까?
///  
/// 2023.7.20 22:41 gitae
/// </summary>
class D2DEffectFactory
{
public:
	D2DEffectFactory() = default;
	~D2DEffectFactory();

	void Initalize(ID2D1DeviceContext* _deviceContext, D2DRenderer* _renderer);
	void Finalize();
	// 
	ID2D1Bitmap* Luminance(ID2D1Bitmap* _orgin);

	ID2D1Bitmap* Cromakey(ID2D1Bitmap* _orgin);

	// 블롬 효과 
	ID2D1Bitmap* BloomEffect(ID2D1Bitmap* _orgin);

	// 이미지를 비트맵으로 바꿔주는 함수
	ID2D1Bitmap* ConvertImageToBitmap(ID2D1Image** _orgin, D2D1_SIZE_U size);

	ID2D1Bitmap* EdgeDetection(ID2D1Bitmap* _orgin);

	// RGB 색상만 추출하는 함수
	ID2D1Bitmap* ExtractColor(ID2D1Bitmap* _orgin, EXTRACT_COLOR _color, float _ratio);

	// 블랜딩 함수
	ID2D1Bitmap* Blend(ID2D1Bitmap* _source, ID2D1Bitmap* _destination, D2D1_BLEND_MODE _mode);

	ID2D1Bitmap* PointDiffuse(ID2D1Bitmap* _origin);

	ID2D1Image* PointDiffuseImage(ID2D1Bitmap* _origin, float _intensity, D2D1_VECTOR_3F _rgb);

	// 스포트라이트 효과
	ID2D1Image* SpotLightImage(ID2D1Bitmap* _origin
		, D2D1_VECTOR_3F _lightPosition
		, D2D1_VECTOR_3F _pointAt
		, float _focus,float _limitConeAngle
		, float _diffuse, D2D1_VECTOR_3F _color);

	// 원형 알파마스크 효과
	ID2D1Image* AlphaMask(ID2D1Image* _orgin, ID2D1Bitmap* _alhpaMap);
private:
	// 포인트 확산 조명효과
	ID2D1Effect* m_pointDiffuse;

	// 스포트라이트 효과
	ID2D1Effect* m_spotDiffuse;

	// 컬러 매트릭스 효과
	ID2D1Effect* m_colorMatrix;

	ID2D1Effect* m_alphaMask;

	// 가우시안 블러
	ID2D1Effect* m_gaussianBlur;

	// 크로마키 효과 
	ID2D1Effect* m_chromakey;

	// 투명도 
	ID2D1Effect* m_opacity;
	
	// 페인팅
	ID2D1Effect* m_flood;

	// 아직 잘 모르겟음
	ID2D1Effect* m_luminanceToAlpha;
	
	// 가장자리 추출
	ID2D1Effect* m_edgeDetection;

	// 여러가지 효과들을 합성
	ID2D1Effect* m_compositeEffect;

	// 블랜딩 전용 
	ID2D1Effect* m_blend;

	D2DRenderer* m_d2DRenderer;
	ID2D1DeviceContext* m_memDC;
	ID2D1DeviceContext* m_deviceContext;
};
