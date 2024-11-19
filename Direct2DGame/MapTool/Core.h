#pragma once
#include "ImguiWindow.h"

struct ID3D11Device;
struct ID3D11ShaderResourceView;
class PathManager;
class GameObject;
class InputManager;
class CameraManager;
class TimeManager;

struct imageinfo
{
	string name;
	ID3D11ShaderResourceView* image;
	int width = 0;
	int height = 0;
	float x;
	float y;
};

class Core :public ImguiWindow
{
public:
	Core(ID3D11Device* g_pd3dDevice,HWND hwnd);
	~Core();

	void Update() override;
	void Render();
	void SettingMenu();

	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	void SaveTextToFile(const wstring& filename);
	void LoadTextToFile(const wstring& filename);
	void SaveAsToFile();
	void LoadAsToFile();
	CameraManager* GetCamera() const { return m_camera; }
	ImVec2 GetScale() const { return m_scale; }
private:
	float f = 0;
	int counter = 0;

	PathManager* m_pathManager;
	Core* m_fileLoad;
	vector<string> m_ImageFiles;
	vector<string> m_imageNames;

	ID3D11Device* g_pd3dDevice;
	vector<imageinfo> images;

	vector<GameObject*> m_objectContainer;
	InputManager* m_input;
	ImVec2 userPos = ImVec2(0.0f, 0.0f);
	CameraManager* m_camera;
	ImVec2 m_scale;
	TimeManager* m_time;
};
