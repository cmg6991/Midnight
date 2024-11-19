#pragma once

#include "pch.h"
class ImguiWindow
{
public:
	ImguiWindow();
	~ImguiWindow();
	virtual void Update()=0;

protected:
	virtual bool Begin(string name);
	void End();
	bool m_show;

	ImguiWindow* imguiwindow;
};

