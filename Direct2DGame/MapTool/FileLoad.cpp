#include "FileLoad.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#pragma comment(lib, "d3d11.lib")
#include <shellapi.h>
#include <commdlg.h>
//#include "Vector2.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "PathManager.h"
#include "FileManager.h"

FileLoad::FileLoad(ID3D11Device* g_pd3dDevice)
	:m_fileLoad(nullptr), g_pd3dDevice(g_pd3dDevice)
	,images{}
{
	m_pathManager = new PathManager();
	m_pathManager->Initalize();
	m_pathManager->GetRelativPath();

	wstring relativePath = m_pathManager->GetRelativPath();

	relativePath += L"\\Resource\\Texture\\";

	vector<wstring> filePaths{};

	FileManager::GetFileMemberPath(filePaths, relativePath, true);

	////이미지 파일 로딩
	for (int i = 0; i < filePaths.size(); i++)
	{
		string convertedPath = " ";

		convertedPath.assign(filePaths[i].begin(),filePaths[i].end()); //wstring을 string으로 변환
		m_ImageFiles.push_back(convertedPath);
	}
	//이미지 파일 불러온거로 info에 저장 
	for (int i = 0; i < m_ImageFiles.size(); i++)
	{
		imageinfo info;
		LoadTextureFromFile(m_ImageFiles[i].c_str(), &info.image, &info.width, &info.height);
		images.push_back(info);
	}
}

FileLoad::~FileLoad()
{

}

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
void FileLoad::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame(); 
	ImGuiIO& io = ImGui::GetIO();
	io.NavActive = false;					//키보드 방향키에 작동하지 않도록 해줌
	io.WantCaptureMouse = true;				//마우스 입력을 받을 수 있게 해줌 

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
				if (ImGui::MenuItem("save"))
					cout << "save clicked" << endl;
				if (ImGui::MenuItem("open"))
					cout << "open clicked" << endl;
				End();
			}
			SettingMenu();
		}
		End();
	}
	
} 
void FileLoad::SettingMenu()
{
	if (!ImGui::CollapsingHeader("Setting"))
		return;

	static ImVec2 backgroundImagePosition(250.f,250.f);
	static ImVec2 backgroundImageOffset(0.f, 0.f);
	static bool isDraggingBackground = false;
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();

	ImGui::BeginChild("scroll", ImVec2(0.0f, 0.0f), true, ImGuiWindowFlags_HorizontalScrollbar);

	int count = 0;
	static int clickedImageIndex = -1; // 이미지 버튼이 눌린 이미지 인덱스를 저장하는 정적 변수
	
	if (!isDraggingBackground)
	{
		for (int i = 0; i < images.size(); i++)
		{
			ImGui::PushID(i);

			// 이미지 버튼을 눌렀을 때 해당 이미지가 배경에 추가되도록 합니다.
			if (ImGui::ImageButton(images[i].image, ImVec2(150.f, 150.f)))
			{
				clickedImageIndex = i;
				isDraggingBackground = false;
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
	// 이미지 버튼이 눌린 이미지에 대해서만 배경에 이미지를 추가합니다.
	if (clickedImageIndex >= 0 && clickedImageIndex < images.size())
	{
		const ImVec2 imageSize(images[clickedImageIndex].width, images[clickedImageIndex].height);
		const ImVec2 topLeft(250.f, 250.f);
		const ImVec2 bottomRight = ImVec2(topLeft.x + imageSize.x, topLeft.y + imageSize.y);

		bgDrawList->AddImage(images[clickedImageIndex].image, topLeft, bottomRight, ImVec2(0, 0), ImVec2(1, 1));
		//배경이미지 드래그
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
		{
			isDraggingBackground = true;
			ImVec2 mousePos = ImGui::GetMousePos();
			backgroundImageOffset.x = mousePos.x - backgroundImagePosition.x;
			backgroundImageOffset.y = mousePos.y - backgroundImagePosition.y;
		}
	}
	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
	{
		isDraggingBackground = false;
	}
	if (isDraggingBackground)
	{
		// 드래그 중인 배경 이미지의 위치
		//ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
		ImVec2 mousePos = ImGui::GetMousePos();
		backgroundImagePosition.x = backgroundImagePosition.x+(mousePos.x - backgroundImageOffset.x);
		backgroundImagePosition.y = backgroundImagePosition.y+(mousePos.y - backgroundImageOffset.y);
	}
}

//파일을 불러오게 해주는 함수
bool FileLoad::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
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

//void FileLoad::Event()
//{
//	ImGuiIO& io = ImGui::GetIO();
//	if (m_mouse == false)
//	{
//		io.MousePos.x, io.MousePos.y
//	}
//}

//void FileLoad::FileOpenDialog()
//{
//	OPENFILENAME OFN;
//	WCHAR lpstrFile[2562] = L"";
//	WCHAR lpCurrentDirectory[1024];
//	wstring CurrentDirectory;
//	GetCurrentDirectory(1024, lpCurrentDirectory);
//	CurrentDirectory = lpCurrentDirectory;
//
//	memset(&OFN, 0, sizeof(OPENFILENAME));
//	OFN.lStructSize = sizeof(OPENFILENAME);
//	OFN.hwndOwner = 
//}
