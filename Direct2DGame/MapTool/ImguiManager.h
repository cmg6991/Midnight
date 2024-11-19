#pragma once
#include "pch.h"
#include <d3d11.h>
#include <map>
#define IMGUIMANAGER ImguiManager::GetInstance()

class ImguiManager
{
public:
	static ImguiManager* GetInstance()
	{
		static ImguiManager singleTone;
		return &singleTone;
	}
	ID3D11ShaderResourceView* CreateShaderResourceView(wstring strFileName);
	ID3D11ShaderResourceView* FindShaderResoucrceView(wstring strFileName);

private:
	struct SpriteResource
	{
		ID3D11ShaderResourceView* m_pSFW;
	};
	map<wstring, SpriteResource*>m_cmSpriteResources;
private:
	ImguiManager();
public:
	~ImguiManager();
};
