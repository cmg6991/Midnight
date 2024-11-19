#include "GameObject.h"
#include "InputManager.h"
#include "CameraManager.h"

GameObject::GameObject()
	: m_texture(nullptr), m_position(), m_isDragging(false), m_offset(0.f, 0.f),
	m_isDelete(false), m_isFixed(false), m_isSelected(false)
{

}

GameObject::~GameObject()
{ 

}

void GameObject::Update(const ImVec2& mousePos, bool isMouseDown, bool isMouseTap)
{
	ImVec2 cameraPosition = GetCamera()->GetPosition();
	ImVec2 cameraScale = GetCamera()->GetScale();

	ImVec2 mouse = mousePos;
	mouse.y += 30.f;

	mouse.x -= cameraPosition.x;
	mouse.y -= cameraPosition.y;

	ImVec2 position{ m_position.x * cameraScale.x , m_position.y * cameraScale.y };


	const ImVec2 imageSize(m_info.width*cameraScale.x, m_info.height*cameraScale.y);
	const ImVec2 topLeft(position.x - imageSize.x * 0.5f, position.y - imageSize.y * 0.5f);
	const ImVec2 bottomRight = ImVec2(topLeft.x + imageSize.x, topLeft.y + imageSize.y);


	if (topLeft.x <= mouse.x && topLeft.y <= mouse.y
		&& bottomRight.x >= mouse.x && bottomRight.y >= mouse.y)
	{
		// 게임오브젝트 드래그 관련 
		if (isMouseDown && !m_isFixed)
		{
			m_isDragging = true;
			if (!m_offset.x && !m_offset.y) {
				m_offset.x = mouse.x - m_position.x * cameraScale.x;
				m_offset.y = mouse.y - m_position.y * cameraScale.y;
			}
		}
		else if (isMouseTap) // 게임 오브젝트 선택관련
		{
			m_isSelected = true;
		}
	}
	else if (isMouseTap)
	{
		m_isSelected = false;
	}

	if (!isMouseDown) {
		m_isDragging = false;	
		m_offset = ImVec2(0.f, 0.f);
	}
	if (m_isDragging == true) {   
		m_position.x = (mouse.x - m_offset.x)/cameraScale.x;
		m_position.y = (mouse.y - m_offset.y)/cameraScale.y;
	}
}

void GameObject::Render()
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();

	ImVec2 cameraPosition = GetCamera()->GetPosition();
	ImVec2 cameraScale = GetCamera()->GetScale();

	ImVec2 position{ m_position.x * cameraScale.x , m_position.y * cameraScale.y };

	ImVec2 renderPosition{ position.x + cameraPosition.x, position.y + cameraPosition.y };

	ImVec2 imageSize(m_info.width*cameraScale.x, m_info.height*cameraScale.y);
	ImVec2 topLeft(renderPosition.x -imageSize.x*0.5f , renderPosition.y - imageSize.y *0.5f);
	ImVec2 bottomRight = ImVec2(topLeft.x + imageSize.x, topLeft.y + imageSize.y);

	bgDrawList->AddImage(m_info.image, topLeft, bottomRight, ImVec2(0, 0), ImVec2(1, 1));
} 

void GameObject::Infomate(int _index)
{
	std::string name = m_info.name + std::to_string(_index);
	
	if (m_isSelected)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::ImColor(0.5f, 1.0f, 0.5f));
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::ImColor(1.0f, 1.0f, 1.0f));
	}
	ImGui::InputFloat2(name.c_str(), &m_position.x);
	ImGui::PopStyleColor(1);

	ImGui::SameLine();
	string Xbutton = std::to_string(_index) + "delete";
	if (ImGui::Button(Xbutton.c_str()))
	{
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::ImColor(0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5, 1.0f, 0.5f));
		ImGui::PopStyleColor(2);

		m_isDelete = true;
	}
	ImGui::SameLine();
	string FixedButton = to_string(_index) + "Fix";
	if (m_isFixed) 
	{
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::ImColor(1.0f, 0.0f, 0.0f));
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::ImColor(0.0f, 0.0f, 0.0f));
	}
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5, 1.0f, 0.5f));

	if (ImGui::Button(FixedButton.c_str()))
	{
		m_isFixed = !m_isFixed;
	}
	ImGui::PopStyleColor(2);
}