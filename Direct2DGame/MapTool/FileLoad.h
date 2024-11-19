#pragma once
#include "ImguiWindow.h"

struct ID3D11Device;
struct ID3D11ShaderResourceView;
class PathManager;

struct imageinfo
{
	ID3D11ShaderResourceView* image;
	int width = 0;
	int height = 0;
	float x;
	float y;
};

class FileLoad :public ImguiWindow
{
public:
	FileLoad(ID3D11Device* g_pd3dDevice);
	~FileLoad();

	void Update() override;
	void SettingMenu();

	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
private:
	float f = 0;
	int counter = 0;

	PathManager* m_pathManager;
	FileLoad* m_fileLoad;
	vector<string> m_ImageFiles;
	ID3D11Device* g_pd3dDevice;
	vector<imageinfo> images;
	bool m_mouse;

};
