#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include "pch.h"
#include "Core.h"
#include "ImguiWindow.h"
#pragma comment(lib, "d3d11.lib")			// D3D11

class InputManager;
class CameraManager;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(const ImVec2& mousePos, bool isMouseDown, bool isMouseTap);
	void Render();
	void Infomate(int index);

	ID3D11ShaderResourceView* GetTexture() const { return m_texture; }
	void SetTexture(ID3D11ShaderResourceView* val) { m_texture = val; }
	ImVec2 GetPosition() const { return m_position; }
	void SetPosition(ImVec2 val) { m_position = val; }
	imageinfo GetInfo() const { return m_info; }
	void SetInfo(imageinfo val) { m_info = val; }
	bool IsDelete() const { return m_isDelete; }
	string GetName() { return m_info.name; }
	int GetIndex() const { return index; }
	void SetIndex(int val) { index = val; }
	CameraManager* GetCamera() const { return m_camera; }
	void SetCamera(CameraManager* val) { m_camera = val; }
	bool IsFixed() const { return m_isFixed; }
	void SetFixed(int val) { m_isFixed = val; }
private:
	ID3D11ShaderResourceView* m_texture;
	ImVec2 m_position;
	bool m_isDragging;
	ImVec2 m_offset;
	imageinfo m_info;
	InputManager* m_inputManager;
	bool m_isDelete;
	bool m_isFixed;
	bool m_isSelected;
	int index;
	CameraManager* m_camera;
};

