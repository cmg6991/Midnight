#pragma once

// 렌더러에 필요한 헤더파일

#include <string>
using std::wstring;

#include <map>
using std::map;

#include <wrl/client.h>
#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <d2d1_1.h>
#include <d2d1_3.h>

#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")
#include <assert.h>
#include <d2d1helper.h>

#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib") // WIC

#include <d3d11.h>			// D3D11
#include <dxgi1_2.h>		// DXGI
#include "d2d1effects_2.h"	// Effect

#pragma comment(lib, "d3d11.lib")			// D3D11
#pragma comment(lib, "dxguid.lib")			// DXGI

using namespace D2D1;

#include "MathModuleHeader.h"

#include "RendererDefine.h"

#include "macro.h"