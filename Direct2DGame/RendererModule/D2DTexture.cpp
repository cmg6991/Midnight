#include "RendererPCH.h"
#include "D2DTexture.h"

Vector2 D2DTexture::GetSize()
{
	D2D1_SIZE_F d2d1_size = m_bitmap->GetSize();

	return Vector2(d2d1_size.width, d2d1_size.height);
}

D2DTexture::D2DTexture():m_bitmap(nullptr)
{

}

D2DTexture::~D2DTexture()
{
	if (m_bitmap != nullptr)
		SafeRelease(&m_bitmap);
}
