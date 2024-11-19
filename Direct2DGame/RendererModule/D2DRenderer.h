#pragma once

#include "D2DEffectFactory.h"

class D2DTexture;
class D2DCamera;

/// <summary>
/// D2D랜더링을 담당한다
/// 
/// </summary>
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	void Initalize(HWND _hwnd);
	void Finalize();

	void BeginRender();
	void EndRender();

public:
	// 화면에 오보젝트가 카메라에 영향을 받는지 확인하는 함수
	void SetCameraAffected(bool _isAffected);

	// 랜더타겟 검은색으로 초기화하는 함수
	void ClearRenderTarget();
	  
	Vector2 GetBitmapSize(const wstring& _name);

public:
	/// 그리기 관련 함수들

	// 직선을 그리는 함수
	void DrawLine(Vector2 _point1, Vector2 _point2
		, ColorF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, ColorF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, float _radius,
		ColorF color = D2D1::ColorF::White);

	void DrawFillElipse(Vector2 _point, Vector2 _scale
		, ColorF _color = D2D1::ColorF::White);

	// 사각형 그리는 함수
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = D2D1::ColorF::White, float _rotation = 0.f);

	// 내부를 채우는 사각형 그리기
	void DrawFillRectangle(Vector2 _position, Vector2 _scale
		, ColorF color = D2D1::ColorF(ColorF::White,1.f), float _rotation = 0.f);

	void DrawFillRectangle2(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = ColorF(ColorF::WhiteSmoke),float _rotation = 0.f);

	// 텍스트 출력함수 
	void DrawTextW(const std::wstring& _str, Vector2 _leftTop
		, Vector2 _rightBottom, ColorF _color = D2D1::ColorF::White
	    , FONT_TYPE _type = FONT_TYPE::DEFALUT );


public:
	D2DTexture* LoadBitmap(const wstring& _key, const wchar_t* _filePath);

	void DrawBitmap(const wstring& _key, Vector2 _position
		, float _rotation = 0.f, float _alpha = 1.f, FLIP_TYPE _type = FLIP_TYPE::NONE
		, Vector2 _scale = Vector2::One);

	// 텍스처를 잘라서 랜더링
	void DrawBitmap(const wstring& _key, Vector2 _position
		, Vector2 _textureLeftTop, Vector2 _sliceSize
		, float _rotation = 0.f, float _alpha = 1.f, FLIP_TYPE _type = FLIP_TYPE::NONE);

	void DrawFreezeBitmap(const wstring& _key, Vector2 _position
		, Vector2 _textureLeftTop, Vector2 _sliceSize , float _ratio
		, float _rotation = 0.f, float _alpha = 1.f, FLIP_TYPE _type = FLIP_TYPE::NONE);
	
	/// 이펙트 관련 함수
	void DrawPointLight(Vector2 _position, float _intensity, D2D1_VECTOR_3F _rgb, Vector2 _scale, float _angle);

	// 블랜딩한 비트맵을 출력한다.
	void DrawBlendBitmap(const wstring& _sourceKey
		, const wstring& _destination
		, D2D1_BLEND_MODE _mode
		, Vector2 _position
		, float _rotation
		, float _alpha = 1.f);

	// Bloom Effect와 함께 비트맵을 그린다.
	void DrawBitmapBloom(const wstring& _key, Vector2 _position
		, float _rotation = 0.f, float _alpha = 1.f);

	void DrawBitmapExtractColor(const wstring& _key, Vector2 _position
		, EXTRACT_COLOR _color, float _rotation = 0.f, float _alpha = 1.f);

	// 스포트라이트 조명 그리기 
	void DrawSpotLight();

	/// <summary>
	/// </summary>
	/// RBG Transition을 적용하는 함수 
	/// <param name="_key"></param>
	/// <param name="_position"></param>
	/// <param name="_rgbOffset">RGB순서대로 오프셋에 넣어서 전달한다</param>
	void DrawRGBTransition(const wstring& _key, Vector2 _position
		, const std::vector<Vector2>& _rgbOffset);

	/// 카메라 관련
	D2DCamera* GetCamera()const { return m_camera; }

private:
	HRESULT LoadBitmapFromFile(PCWSTR _filePath
		, UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _bitmap);

private:
	/// 랜더타겟을 만드는 함수
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

private:
	void SetTransform(float _radian, Vector2 _point);
	// 기본 행렬로 변환
	void SetTransform() { m_deviceContext->SetTransform(m_finalMatrix); }

	void SetFlip(FLIP_TYPE _type, Vector2 _position);
private:
	D2D1_MATRIX_3X2_F m_screenMatrix; // 스크린 좌표계로 변환하는 행렬
	D2D1_MATRIX_3X2_F m_finalMatrix;

	HWND m_hwnd; // 메인 윈도우 핸들
	ID2D1Factory1* m_factory; // 팩토리
	IDWriteFactory* m_writeFactory; // 쓰기 전용 팩토리

	IDWriteTextFormat* m_textFormat[static_cast<int>(FONT_TYPE::END)]; // 텍스트 형식

	ID2D1SolidColorBrush* m_tempBrush; // 잠시 사용하는 용도

	ID2D1DeviceContext* m_deviceContext; // 렌더타겟
	D3D_FEATURE_LEVEL m_featureLevel; 
	ID2D1Device* m_device; // D2D Deivice;
	IDXGISwapChain1* m_swapChain; // 스왑체인
	ID2D1CommandList* m_commandList; 

	ID2D1Bitmap1* m_memoryBitamap; 
	ID2D1Bitmap1* m_copyBitmap;

 	float m_dpi;

private:
	// 디바이스 종속적인 자원들이 준비되었는가?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;

private:
	bool m_cameraAffected;

	/// 비트맵 관련 
	IWICImagingFactory* m_imagingFactorty;

	/// 텍스처를 저장하는 공간
	map<wstring, D2DTexture*> m_textures; 

	/// 카메라 관련
	D2DCamera* m_camera;

	/// 이펙트 
	D2DEffectFactory* m_effectFactory ;

	// SetTransform을 사용하기위한 friend 선언
	friend ID2D1Bitmap* D2DEffectFactory::ConvertImageToBitmap(ID2D1Image** _orgin, D2D1_SIZE_U size);
};

