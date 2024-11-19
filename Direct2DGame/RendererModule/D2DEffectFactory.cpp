#include "RendererPCH.h"
#include "D2DEffectFactory.h"
#include "D2DRenderer.h"

D2DEffectFactory::~D2DEffectFactory()
{

}

void D2DEffectFactory::Initalize(ID2D1DeviceContext* _deviceContext, D2DRenderer* _renderer)
{
	m_deviceContext = _deviceContext;
	m_d2DRenderer = _renderer;

	// 이펙트 생성
	m_deviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &m_gaussianBlur);
	m_deviceContext->CreateEffect(CLSID_D2D1LuminanceToAlpha, &m_luminanceToAlpha);
	m_deviceContext->CreateEffect(CLSID_D2D1Flood, &m_flood);
	m_deviceContext->CreateEffect(CLSID_D2D1Composite, &m_compositeEffect);
	m_deviceContext->CreateEffect(CLSID_D2D1Opacity, &m_opacity);
	m_deviceContext->CreateEffect(CLSID_D2D1ChromaKey, &m_chromakey);
	m_deviceContext->CreateEffect(CLSID_D2D1EdgeDetection, &m_edgeDetection);
	m_deviceContext->CreateEffect(CLSID_D2D1Blend, &m_blend);
	m_deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &m_colorMatrix);
	m_deviceContext->CreateEffect(CLSID_D2D1PointDiffuse, &m_pointDiffuse);
	m_deviceContext->CreateEffect(CLSID_D2D1AlphaMask, &m_alphaMask);
	m_deviceContext->CreateEffect(CLSID_D2D1SpotSpecular, &m_spotDiffuse);
}

void D2DEffectFactory::Finalize()
{
	// 이팩트 해제
	m_colorMatrix->Release();
	m_gaussianBlur->Release();
	m_chromakey->Release();
	m_opacity->Release();
	m_flood->Release();
	m_luminanceToAlpha->Release();
	m_edgeDetection->Release();
	m_compositeEffect->Release();
	m_blend->Release();
	m_pointDiffuse->Release();
}

ID2D1Bitmap* D2DEffectFactory::Luminance(ID2D1Bitmap* _orgin)
{
	m_luminanceToAlpha->SetInput(0, _orgin);

	// LuminanceToAlpha result is composited on top of a white surface to show opacity.
	m_flood->SetValue(D2D1_FLOOD_PROP_COLOR, D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f));

	ID2D1Effect* compositeEffect;
	m_deviceContext->CreateEffect(CLSID_D2D1Composite, &compositeEffect);

	m_compositeEffect->SetInputEffect(0, m_flood);
	m_compositeEffect->SetInputEffect(1, m_luminanceToAlpha);

	ID2D1Image* outputImage = nullptr;
	m_compositeEffect->GetOutput(&outputImage);

	outputImage;

	return nullptr;
}

ID2D1Bitmap* D2DEffectFactory::Cromakey(ID2D1Bitmap* _orgin)
{
	ID2D1Bitmap* resultBitmap = nullptr;
	ID2D1Image* image = nullptr;

	static float r = 0.5f;

	m_chromakey->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.5f, 0.5f, 0.5f));
	m_chromakey->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.7f);
	m_chromakey->SetInput(0, _orgin);

	m_chromakey->GetOutput(&image);

	D2D1_SIZE_U size = { static_cast<UINT32>(_orgin->GetSize().width)
		,static_cast<UINT32>(_orgin->GetSize().height) };

	resultBitmap = ConvertImageToBitmap(&image, size);

	return resultBitmap;
}

ID2D1Bitmap* D2DEffectFactory::BloomEffect(ID2D1Bitmap* _orgin)
{
	ID2D1Bitmap* resultBitmap = nullptr;
	ID2D1Image* image = nullptr;

	// 원본 이미지 투명도 50퍼 적용
	m_opacity->SetInput(0, _orgin);
	m_opacity->SetValue(D2D1_OPACITY_PROP_OPACITY, 0.9f);

	ID2D1Bitmap* cromakey = Cromakey(_orgin);

	// 가우시안 블러를 적용한 비트맵
	m_gaussianBlur->SetInput(0, cromakey);
	m_gaussianBlur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 30.f);

	m_compositeEffect->SetValue(D2D1_COMPOSITE_PROP_MODE, D2D1_COMPOSITE_MODE_PLUS);
	m_compositeEffect->SetInputEffect(0, m_gaussianBlur);
	m_compositeEffect->SetInputEffect(1, m_opacity);

	m_compositeEffect->GetOutput(&image);
	D2D1_SIZE_U size = { static_cast<UINT32>(_orgin->GetSize().width)
		, static_cast<UINT32>(_orgin->GetSize().height) };

	resultBitmap = ConvertImageToBitmap(&image, size);

	image->Release();
	cromakey->Release();
	return resultBitmap;
}

ID2D1Bitmap* D2DEffectFactory::ConvertImageToBitmap(ID2D1Image** _orgin, D2D1_SIZE_U size)
{
	ID2D1Image* oldTarget = NULL;
	ID2D1Bitmap1* targetBitmap = NULL;

	// "D2D1_BITMAP_OPTIONS_TARGET" 모드로 적절한 비트맵을 생성.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);

	m_deviceContext->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);

	// 행렬은 원래대로 변환
	m_deviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
		
	// 현재 타겟을 저장 해둔다. 그리고 새로 그릴 ID2D1Bitmap 으로 바꿈.
	m_deviceContext->GetTarget(&oldTarget);
	m_deviceContext->SetTarget(targetBitmap);
	// DC 에 Image를 그림.
	m_deviceContext->Clear();

	m_deviceContext->DrawImage((*_orgin), D2D1::Point2F(0.f, 0.f));

	// 비트맵에 해당되는 이미지가 그려졌으므로 해당 비트맵을 리턴한다.
	m_deviceContext->SetTarget(oldTarget);

	// 다그린후에는 행렬은 기본으로 변환
	m_d2DRenderer->SetTransform();

	oldTarget->Release();

	return targetBitmap;
}

ID2D1Bitmap* D2DEffectFactory::EdgeDetection(ID2D1Bitmap* _orgin)
{
	ID2D1Bitmap* resultBitmap = nullptr;
	ID2D1Image* image = nullptr;

	m_edgeDetection->SetInput(0, _orgin);
	m_edgeDetection->SetValue(D2D1_EDGEDETECTION_PROP_STRENGTH, 0.5f);
	m_edgeDetection->SetValue(D2D1_EDGEDETECTION_PROP_BLUR_RADIUS, 0.0f);
	m_edgeDetection->SetValue(D2D1_EDGEDETECTION_PROP_MODE, D2D1_EDGEDETECTION_MODE_SOBEL);
	m_edgeDetection->SetValue(D2D1_EDGEDETECTION_PROP_OVERLAY_EDGES, false);
	m_edgeDetection->SetValue(D2D1_EDGEDETECTION_PROP_ALPHA_MODE, D2D1_ALPHA_MODE_PREMULTIPLIED);

	m_edgeDetection->GetOutput(&image);
	D2D1_SIZE_U size = { static_cast<UINT32>(_orgin->GetSize().width)
		, static_cast<UINT32>(_orgin->GetSize().height) };

	resultBitmap = ConvertImageToBitmap(&image, size);

	return resultBitmap;
}

ID2D1Bitmap* D2DEffectFactory::ExtractColor(ID2D1Bitmap* _orgin, EXTRACT_COLOR _color, float _ratio)
{
	ID2D1Bitmap* resultBitmap = nullptr;
	ID2D1Image* image = nullptr;

	float R = 0.f, G = 0.f, B = 0.f;
	
	switch (_color)
	{
	case EXTRACT_COLOR::RED:
		R = 1.f;
		break;
	case EXTRACT_COLOR::BLUE:
		B = 1.f;
		R = _ratio;
		G = 0.25f + _ratio*0.75f;
		break;
	case EXTRACT_COLOR::GREEN:
		G = 1.f;
		break;
	default:
		break;
	}

	// [R B G A] 행렬과 matrix 행렬을 연산해서 최종적인 색깔을 만든다. 
	D2D1::Matrix5x4F matrix(
		R, 0, 0, 0,
		0, G, 0, 0,
		0, 0, B, 0,
		0, 0, 0, 1,
		0, 0, 0, 0);

	m_colorMatrix->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
	m_colorMatrix->SetInput(0, _orgin);

	m_colorMatrix->GetOutput(&image);
	D2D1_SIZE_U size = { static_cast<UINT32>(_orgin->GetSize().width)
		, static_cast<UINT32>(_orgin->GetSize().height) };

	resultBitmap = ConvertImageToBitmap(&image, size);

	return resultBitmap;
}

ID2D1Bitmap* D2DEffectFactory::Blend(ID2D1Bitmap* _source, ID2D1Bitmap* _destination, D2D1_BLEND_MODE _mode)
{
	ID2D1Image* image = nullptr;

	m_blend->SetValue(D2D1_BLEND_PROP_MODE, _mode);

	m_blend->SetInput(0, _source);
	m_blend->SetInput(1, _destination);

	m_blend->GetOutput(&image);
	D2D1_SIZE_U size = { static_cast<UINT32>(_destination->GetSize().width)
		, static_cast<UINT32>(_destination->GetSize().height) };

	return ConvertImageToBitmap(&image, size);
}

ID2D1Bitmap* D2DEffectFactory::PointDiffuse(ID2D1Bitmap* _origin)
{
	ID2D1Bitmap* resultBitmap = nullptr;
	ID2D1Image* image = nullptr;

	static float intensity = 1.f;
	intensity += 0.01f;

	m_pointDiffuse->SetInput(0, _origin);
	m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_LIGHT_POSITION, Vector3F(250.f, 250.0f, 1.1f));
	m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_DIFFUSE_CONSTANT, intensity);
	m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_COLOR, Vector3F(0.f,0.f,1.0f));

	m_pointDiffuse->GetOutput(&image);

	D2D1_SIZE_U size = { static_cast<UINT32>(_origin->GetSize().width) 
	, static_cast<UINT32>(_origin->GetSize().height) };


	return ConvertImageToBitmap(&image,size);
}

ID2D1Image* D2DEffectFactory::PointDiffuseImage(ID2D1Bitmap* _origin, float _intensity, D2D1_VECTOR_3F _rgb)
{
	ID2D1Image* image = nullptr;

	m_pointDiffuse->SetInput(0, _origin);
	m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_LIGHT_POSITION, Vector3F(500.f, 500.0f, 1.f));
	m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_DIFFUSE_CONSTANT, _intensity);    
	m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_COLOR, _rgb);
	//m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_KERNEL_UNIT_LENGTH, D2D1_VECTOR_2F{1.f,1.f});
	//m_pointDiffuse->SetValue(D2D1_POINTDIFFUSE_PROP_SCALE_MODE, D2D1_POINTDIFFUSE_SCALE_MODE_HIGH_QUALITY_CUBIC);

	m_pointDiffuse->GetOutput(&image);

	return image;
}

ID2D1Image* D2DEffectFactory::SpotLightImage(ID2D1Bitmap* _origin
	, D2D1_VECTOR_3F _lightPosition
	, D2D1_VECTOR_3F _pointAt
	, float _focus, float _limitConeAngle
	, float _diffuse, D2D1_VECTOR_3F _color)
{
	ID2D1Image* image = nullptr;

	m_spotDiffuse->SetInput(0, _origin);
	m_spotDiffuse->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, _lightPosition);
	m_spotDiffuse->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, _pointAt);
	m_spotDiffuse->SetValue(D2D1_SPOTSPECULAR_PROP_FOCUS, _focus);
	m_spotDiffuse->SetValue(D2D1_SPOTSPECULAR_PROP_LIMITING_CONE_ANGLE, _limitConeAngle);
	m_spotDiffuse->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_CONSTANT, _diffuse);
	m_spotDiffuse->SetValue(D2D1_SPOTSPECULAR_PROP_COLOR, _color);

	m_spotDiffuse->GetOutput(&image);

	return image;
}

ID2D1Image* D2DEffectFactory::AlphaMask(ID2D1Image* _orgin, ID2D1Bitmap* _alhpaMap)
{
	ID2D1Image* image;

	m_alphaMask->SetInput(0, _orgin);
	m_alphaMask->SetInput(1, _alhpaMap);

	m_alphaMask->GetOutput(&image);

	return image;
}
