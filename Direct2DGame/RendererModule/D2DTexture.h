#pragma once
#include "D2DResource.h"

/// <summary>
/// 비트맵 정보를 저장하고 있는 텍스처
/// </summary>
class D2DTexture :
    public D2DResource
{
public:
    // 비트맵의 사이즈를 반환한다.
    Vector2 GetSize();

private:
    void SetBitMap(ID2D1Bitmap* _bitmap) { m_bitmap = _bitmap; }
    ID2D1Bitmap* GetBitmap() { return m_bitmap;}

    D2DTexture();
	~D2DTexture();

    ID2D1Bitmap* m_bitmap; // 비트맵 정보

    friend class D2DRenderer;
};
 
