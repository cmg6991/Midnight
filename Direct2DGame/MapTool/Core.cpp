#include "Core.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#include <fstream>
#include <sstream>
#pragma comment(lib, "d3d11.lib")
#include <shellapi.h>
#include <commdlg.h>
#include <algorithm>
//#include "Vector2.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "PathManager.h"
#include "FileManager.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "GameObject.h"

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
Core::Core(ID3D11Device* g_pd3dDevice, HWND hwnd)
	:m_fileLoad(nullptr), g_pd3dDevice(g_pd3dDevice)
	,images{}
{
	m_pathManager = new PathManager();
	m_pathManager->Initalize();
	m_pathManager->GetRelativPath();

	m_input = new InputManager();
	m_input->Initalize(hwnd);

	m_camera = new CameraManager(m_input);

	m_time = new TimeManager();
	m_time->Initalize();

	wstring relativePath = m_pathManager->GetRelativPath();

	relativePath += L"\\Resource\\Texture\\MapSource";

	vector<wstring> filePaths{};
	vector<wstring> fileName{};

	FileManager::GetFileMemberPath(filePaths, relativePath, true);
	FileManager::GetFileMemberName(fileName, relativePath, true);

	////이미지 파일 로딩
	for (int i = 0; i < filePaths.size(); i++)
	{
		string convertedPath = " ";

		convertedPath.assign(filePaths[i].begin(),filePaths[i].end()); //wstring을 string으로 변환
		m_ImageFiles.push_back(convertedPath);
	}
	for (int i = 0; i < fileName.size(); i++)
	{
		string convertedName = " ";

		convertedName.assign(fileName[i].begin(), fileName[i].end()); //wstring을 string으로 변환
		m_imageNames.push_back(convertedName);
	}
	//이미지 파일 불러온거로 info에 저장 
	for (int i = 0; i < m_ImageFiles.size(); i++)
	{
		imageinfo info;
		LoadTextureFromFile(m_ImageFiles[i].c_str(), &info.image, &info.width, &info.height);
		info.name = m_imageNames[i];
		images.push_back(info);
	}

}

Core::~Core()
{

}

void Core::Update()
{
	//ImTextureID backgroundTexture = ImGui_ImplDX11_AddTextureFromFile("background.jpg");
	m_input->Update();
	double deltaTime = m_time->Update();
	m_camera->Update(deltaTime);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame(); 
	ImGuiIO& io = ImGui::GetIO();
	io.NavActive = false;					//키보드 방향키에 작동하지 않도록 해줌
	io.WantCaptureMouse = true;				//마우스 입력을 받을 수 있게 해줌 

	for (int i = 0; i < m_objectContainer.size(); ++i)
	{
		m_objectContainer[i]->Update(m_input->GetMousePosition(), m_input->IsKeyState(KEY::LMOUSE, KEY_STATE::HOLD), m_input->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP));
	}
	if (m_show)
	{
		if (!Begin("Pocari"))
		{
			End();
		}
		else
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
					SaveAsToFile();
				if (ImGui::MenuItem("Load"))
					LoadAsToFile();
				End();
			}
			SettingMenu();
			for (int i = 0; i < m_objectContainer.size(); ++i)
			{
				m_objectContainer[i]->Infomate(i);
			} 
		}
		End();
		
	}

	Render();

	// 오브젝트 삭제 처리
	for (auto iter = m_objectContainer.begin(); iter != m_objectContainer.end();)
	{
		if ((*iter)->IsDelete())
		{
			delete* iter;
			iter = m_objectContainer.erase(iter);
		}
		else
		{
			++iter;
		}
	}
} 

void Core::Render()
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	
	ImVec2 cameraPosition = GetCamera()->GetPosition();
	ImVec2 cameraScale = GetCamera()->GetScale();

	
	for (int i = 0; i < 6; ++i)
	{

		const ImVec2 imageSize(images[0].width * cameraScale.x, images[0].height * cameraScale.y);
		ImVec2 position{ cameraPosition.x + images[0].width*i*cameraScale.x , cameraPosition.y};
		//position.x *= cameraScale.x;

	    const ImVec2 topLeft(position.x, position.y);
	    const ImVec2 bottomRight = ImVec2(topLeft.x + imageSize.x, topLeft.y + imageSize.y);

		bgDrawList->AddImage(images[0].image, topLeft, bottomRight, ImVec2(0, 0), ImVec2(1, 1));
	}

	for (int i = 0; i < m_objectContainer.size(); ++i)
	{	
		m_objectContainer[i]->Render();
	}
}

void Core::SettingMenu()
{
	if (!ImGui::CollapsingHeader("Setting"))
		return;

	static ImVec2 backgroundImagePosition(250.f,250.f);
	static ImVec2 backgroundImageOffset(0.f, 0.f);
	static bool isDraggingBackground = false;


	ImGui::BeginChild("scroll", ImVec2(0.0f, 0.0f), true, ImGuiWindowFlags_HorizontalScrollbar);

	int count = 0;
	static int clickedImageIndex = -1; // 이미지 버튼이 눌린 이미지 인덱스를 저장하는 정적 변수
	
	if (!isDraggingBackground)
	{
		for (int i = 0; i < images.size(); i++)
		{
			ImGui::PushID(i);

			// 이미지 버튼을 눌렀을  때 해당 이미지가 배경에 추가되도록 합니다.
			if (ImGui::ImageButton(images[i].image, ImVec2(150.f, 150.f)))
			{
				clickedImageIndex = i;
				isDraggingBackground = false;

				/// 오브젝트를 생성해서 배경에 출력
				GameObject* object = new GameObject();
				object->SetTexture(images[clickedImageIndex].image);
			
				ImVec2 position = m_camera->GetPosition();
				ImVec2 scale = m_camera->GetScale();
				
				position.x *= -1.f;
				position.y *= -1.f;

				position.x += 960.f;
				position.y += 540.f;

				position.x /= scale.x;
				position.y /= scale.y;


				object->SetPosition(position);
				object->SetInfo(images[clickedImageIndex]);
				object->SetIndex(clickedImageIndex);
				object->SetCamera(m_camera);

				m_objectContainer.push_back(object);
			}

			ImGui::PopID();

			count++;
			if (count < 3)
				ImGui::SameLine();
			else
				count = 0;
		}
	}

	ImGui::EndChild();
}

//파일을 불러오게 해주는 함수
bool Core::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}

void Core::SaveTextToFile(const wstring& filename)
{
	std::wofstream file(filename);
	if (!file.is_open())
	{
		cout << "Failed to open file for writing." << endl;
		return;
	}
	for (int i = 0; i < m_objectContainer.size(); i++)
	{
		m_objectContainer[i]->GetPosition();
		ImVec2 position = m_objectContainer[i]->GetPosition();
		int index = m_objectContainer[i]->GetIndex();
		file << index << " "<< position.x << " " << position.y << endl;
	}
	file.close();
}

void Core::LoadTextToFile(const wstring& filename)
{
	std::wifstream file(filename);
	if (!file.is_open())
	{
		cout << "Failed to open file for writing" << endl;
		return;
	}

	for (int i = 0; i < m_objectContainer.size(); i++)
	{
		delete m_objectContainer[i];
	}
	m_objectContainer.clear();

	wstring line;
	while (std::getline(file, line))
	{
		std::wistringstream iss(line);
		int index;
		float x, y;
		static int clickedImageIndex = -1;

		if (iss >> index >> x >> y)
		{
			clickedImageIndex = index;
			GameObject* object = new GameObject();
			object->SetIndex(index);
			object->SetPosition(ImVec2(x, y));
			object->SetTexture(images[clickedImageIndex].image);
			object->SetInfo(images[clickedImageIndex]);
			object->SetIndex(clickedImageIndex);
			object->SetCamera(m_camera);
			object->SetFixed(true);

			m_objectContainer.push_back(object);
		}
	}
	file.close();
}

void Core::SaveAsToFile()
{
	OPENFILENAME ofn;
	TCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"txt";

	if (GetSaveFileName(&ofn) == TRUE) {
		SaveTextToFile(szFileName);
	}
}

void Core::LoadAsToFile()
{
	OPENFILENAME ofn;
	TCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"txt";

	if (GetOpenFileName(&ofn) == TRUE)
	{
		LoadTextToFile(szFileName);
	}
}