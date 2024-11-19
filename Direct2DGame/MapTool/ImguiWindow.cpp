#include "ImguiWindow.h"
#include "imgui.h"

ImguiWindow::ImguiWindow()
	:m_show(true), imguiwindow(nullptr)
{

}

ImguiWindow::~ImguiWindow()
{

}

bool ImguiWindow::Begin(string name)
{
	return ImGui::Begin(name.c_str(), &m_show);
}

void ImguiWindow::End()
{
	ImGui::End();
}